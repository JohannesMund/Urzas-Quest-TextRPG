#include "cwonderlamp.h"

#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"
#include "randomizer.h"
#include "wonderlamp/companion/cdjinncompanion.h"
#include "wonderlamp/items/cgem.h"
#include "wonderlamp/moduleressources.h"
#include "wonderlamp/npc/cgenie.h"
#include "wonderlamp/npc/djinnfactory.h"

#include <math.h>
#include <nlohmann/json.hpp>

CWonderLamp::CWonderLamp() : CItem(TagNames::WonderLamp::wonderlamp)
{
    _name = WonderLamp::wonderlamp();
    _description = tr("A beautiful lamp, golden and decorated with gems. Just like in the fairy tales. You should try "
                      "and rub it. Who knows?");
    _isUsableFromInventory = true;
    _isUsableFromBattle = true;
    _isSellable = false;
    _value = 10;
    _lastCaredFor = std::max(1U, CGameManagement::now() - Randomizer::getRandom(50));

    if (Randomizer::getRandomEntry<Core::EGender>({Core::EGender::eFemale, Core::EGender::eMale}) ==
        Core::EGender::eFemale)
    {
        _djinn = new CJeannie();
    }
    else
    {
        _djinn = new CGenie();
    }
    _djinnCompanion = new CDjinnCompanion(_djinn);
}

CWonderLamp::~CWonderLamp()
{
    if (_djinn != nullptr)
    {
        if (_djinn->isSignificantOther())
        {
            CGameManagement::getPlayerInstance()->setSignificantOther(nullptr);
        }

        delete _djinn;
    }
    if (_djinnCompanion != nullptr)
    {
        delete _djinnCompanion;
    }
}

void CWonderLamp::useFromInventory()
{
    CMenuAction input;
    do
    {
        Console::cls();
        Console::printLn(
            tr("Your wonderful {}. You want to rub it. You always want to rub ist, but you also want to care about "
               "this precious artifact. It probably needs some cleaning, and a little repair now and then.",
               WonderLamp::wonderlamp()));

        CMenu menu(WonderLamp::moduleName());
        auto rubAction = menu.createAction({"Rub", 'R'});
        auto examineAction = menu.createAction({"Examine", 'E'});

        CMenu::ActionList bottleList = {rubAction, examineAction};

        menu.addMenuGroup(bottleList, {CMenu::exit()});
        input = menu.execute();

        if (input == examineAction)
        {
            examine();
        }

        if (input == rubAction)
        {
            rubTheLamp();
        }
    } while (input != CMenu::exit());
}

void CWonderLamp::useFromBattle(CEnemy*)
{

    Console::printLn(tr("Rough times require the big guns. You rub your {} and call {} to help you in battle.",
                        WonderLamp::wonderlamp(),
                        _djinn->name()));
    useWish();
    Console::printLn(tr("{} joins you in battle.", _djinn->name()));

    CGameManagement::getPlayerInstance()->addSupportCompanion(_djinnCompanion);
}

CItem::ItemFilter CWonderLamp::wonderlampFilter()
{
    return [](const CItem* item) { return dynamic_cast<const CWonderLamp*>(item) != nullptr; };
}

nlohmann::json CWonderLamp::save() const
{
    nlohmann::json json = CItem::save();

    json["Wasted"] = _wasted;
    json["WishesLeft"] = _wishesLeft;
    json["MissingGem"] = _missingGem;
    json["LastCaredFor"] = _lastCaredFor;

    json["Djinn"] = _djinn->save();

    return json;
}

void CWonderLamp::load(const nlohmann::json& json)
{
    CItem::load(json);

    _wasted = json["Wasted"];
    _wishesLeft = json["WishesLeft"];
    _missingGem = json["MissingGem"];
    _lastCaredFor = json["LastCaredFor"];

    _djinn->load(json);
}

std::string CWonderLamp::translatorModuleName() const
{
    return std::string(WonderLamp::moduleName());
}

void CWonderLamp::rubTheLamp()
{
    if (_wasted)
    {
        Console::printLn(tr("You rub and rub, but nothing happens. But you can try to rub again."));
        Console::br();
        Console::confirmToContinue();
        return;
    }

    CMenuAction input;
    do
    {
        Console::cls();
        Console::printLn(
            tr("With a lot of smoke, even more sparkling, and a loud \"Wooosh\" noise, {} Appears out of the {}. As "
               "your personal djinn, {} grants you a total of 3 life saving support actions in battle. But also, as "
               "your presonal djinn, rules can be bent when a djinn likes nor dislikes {} master.",
               _djinn->name(),
               WonderLamp::wonderlamp(),
               _djinn->heShe(),
               _djinn->hisHer()));
        Console::br();
        adjustWishes();

        CMenu menu(WonderLamp::moduleName());

        auto djinnAction = _djinn->npcNav(menu);
        menu.addMenuGroup({}, {djinnAction});

        CMenu::ActionList djinnList;

        auto visitAction = menu.createAction({"Visit Bottle", 'V'});
        if (_djinn->sympathy() >= CNpc::ESympathyLevel::eLike)
        {
            djinnList.push_back(visitAction);
        }

        menu.addMenuGroup({djinnList}, {CMenu::exit()});
        input = menu.execute();
        if (input == djinnAction)
        {
            _djinn->interact();
        }
        if (input == visitAction)
        {
            visitBottle();
        }
    } while (input != CMenu::exit());
}

void CWonderLamp::examine()
{
    if (_wasted)
    {
        Console::printLn(tr("You take a close look at your {}. It is dirty, it is broken and most important: "
                            "it is empty. it is a worthless piece of trash. You do not bother to clean it.",
                            WonderLamp::wonderlamp()));
        Console::br();
        Console::confirmToContinue();
        return;
    }

    CMenuAction input;
    do
    {
        CMenu menu(WonderLamp::moduleName());

        auto cleanAction = menu.createAction({"Clean", 'C'});
        auto replaceAction = menu.createAction({"Replace missing gem", 'R'});
        auto stealAction = menu.createAction({"Steal Gem", 'S'});

        CMenu::ActionList careList;

        if (needsCleaning())
        {
            Console::printLn(tr("You can see, that your {} is loved and used often. The polish is getting dull and "
                                "some scratches appear"));
            const auto decay = CGameManagement::now() - _lastCaredFor;
            _missingGem = _missingGem || Randomizer::getRandom(decay) > 50;
            careList.push_back(cleanAction);
        }

        if (_missingGem)
        {
            Console::printLn(
                tr("Turns out, there is a gem missing on your {}. You should replace it.", WonderLamp::wonderlamp()));
            if (CGameManagement::getInventoryInstance()->hasItem(CGem::CGem::gemFilter()))
            {
                careList.push_back(replaceAction);
            }
            else
            {
                tr("Unfortunately, you do not have gems, so you should keep your eyes open.");
            }
        }
        else
        {
            Console::printLn(
                tr("This {} is loaded with gems. They are worth a fortune. This could be really helpful "
                   "solving the one or the other financial crisis. One gem more or less... No one will notice."));
            careList.push_back(stealAction);
        }

        menu.addMenuGroup(careList, {CMenu::exit()});
        input = menu.execute();

        if (input == cleanAction)
        {
            clean();
        }
        if (input == replaceAction)
        {
            replaceGem();
        }
        if (input == stealAction)
        {
            stealGem();
        }

    } while (input == CMenu::exit());
}

void CWonderLamp::visitBottle()
{
    CMenuAction input;
    do
    {
        Console::cls();
        Console::printLn(tr("You ask {} to visit him, and {} happily aggrees. With the known \"Slurp\" noise, you "
                            "materialize inside the magic bottle.",
                            _djinn->name(),
                            _djinn->heShe()));
        Console::printLn(tr("The inside of the {} is cozy, richly decorated and just a little kitschy. There is a "
                            "comfortable sofa for you to sit on.",
                            WonderLamp::wonderlamp()));
        if (needsCleaning())
        {
            Console::printLn(
                tr("But, this place could use some cleaning. You remember, that it has been a while, since "
                   "you last cared for the {}, maybe it is about time.",
                   WonderLamp::wonderlamp()));
        }

        if (_missingGem)
        {
            Console::printLn(tr("The place could be more magical, but the mafic is channeled through the gems on the "
                                "outside of the {}. "
                                "You should have a look, whether everything is in order with those gems.",
                                WonderLamp::wonderlamp()));
        }
        Console::printLn(
            tr("You take a seat on the sofa together with {}, and you ask yourselfs, how to spend your time together.",
               _djinn->name()));

        CMenu menu(WonderLamp::moduleName());
        auto guessTheNumberAction = menu.createAction({"Play \"Guess the Number\"", 'G'});
        auto ludoAction = menu.createAction({"Play \"Ludo\"", 'L'});
        auto cozyCardsAction = menu.createAction({"Play a Cozy cardgame", 'C'});
        CMenu::ActionList games = {guessTheNumberAction, ludoAction, cozyCardsAction};

        auto spendTimeAction = menu.createAction({"Spend some time", 'S'});
        menu.addMenuGroup(games);
        menu.addMenuGroup({spendTimeAction}, {CMenu::exit()});
        input = menu.execute();

        if (input == spendTimeAction)
        {
            spendTimeInside();
        }

        if (input == guessTheNumberAction)
        {
            playGuessTheNumber();
        }
        if (input == ludoAction)
        {
            playLudo();
        }
        if (input == cozyCardsAction)
        {
            playCards();
        }

    } while (input == CMenu::exit());
}

void CWonderLamp::replaceGem()
{
    auto gem = CGameManagement::getInventoryInstance()->getFirstItemByFilter<CGem>(CGem::gemFilter());
    if (!gem.has_value())
    {
        Console::printLn(tr("You dont have a gem. maybe later."));
        return;
    }

    Console::printLn(tr("There is a gap on your {} where the gem fell of (or has been acidentally fallen of). You "
                        "decide to replace it with a beautiful "
                        "{}. Looks like new.",
                        WonderLamp::wonderlamp(),
                        gem.value()->name()));
    Console::printLn(tr("{} seems to like the new gem.", _djinn->name()));
    _djinn->addSympathy(25 + Randomizer::getRandom(25));
    if (needsCleaning())
    {
        Console::br();
        Console::printLn(
            tr("The {} might be new, and it sparkles beautifully. But your {} should use another cleaning.",
               gem.value()->name(),
               WonderLamp::wonderlamp()));
    }
    CGameManagement::getInventoryInstance()->removeItem(gem.value());

    Console::br();
    Console::confirmToContinue();
}

void CWonderLamp::stealGem()
{
    Console::printLn(tr("Ok, not the nicest move, to steal from {}s home, but you need the money. Gems fall of here "
                        "and than, it was an accident, nobody will notice.",
                        _djinn->name()));
    Console::printLn(tr("You snitch off one of the gems and put it into your pocket."));
    CGameManagement::getInventoryInstance()->addItem(new CGem());
    _djinn->addSympathy((Randomizer::getRandom(50) * -1) - 25);
    _missingGem = true;
    Console::printLn(tr("Turns out, {} noticed.", _djinn->heShe()));
    Console::br();
    Console::confirmToContinue();
}

void CWonderLamp::clean()
{
    Console::printLn(tr("You take some time, and clean your {}. Carefully you remove dirt, polish out the scratches "
                        "and let the gems shine again.",
                        WonderLamp::wonderlamp()));
    if (_missingGem)
    {
        Console::printLn(tr("Speaking of shiny gems, one is missing, you should replace it soon."));
    }

    Console::br();
    Console::printLn(tr("Finally, the home of {} is nice and clean again", _djinn->name()));
    _djinn->addSympathy(5 + Randomizer::getRandom(20));

    _lastCaredFor = CGameManagement::now();
    Console::br();
    Console::confirmToContinue();
}

void CWonderLamp::useWish()
{
    _wishesLeft--;
    Console::printLn(tr("You use up one of your wishes."));
    adjustWishes(true);
}

void CWonderLamp::adjustWishes(const bool print)
{
    if (_djinn->sympathy() >= CNpc::ESympathyLevel::eLike)
    {
        if (print)
        {
            Console::printLn(
                tr("...but appearently, this this wish does not count towards your wishes. {} explaines it to "
                   "you in detail, but your knowledge in genie-law leaves... well, room for improvement.",
                   _djinn->name()));
            Console::printLn(tr("Turns out, you are back to your full wishes, and you do not question it."));
        }

        _wishesLeft = 3;
    }

    if (_djinn->sympathy() == CNpc::ESympathyLevel::eHate)
    {
        if (print)
        {
            Console::printLn(tr("{} explains alot, reciting genie-law and this service also counts as wish, and all of "
                                "this is totally confusing.",
                                _djinn->name()));
        }

        _wishesLeft = std::min(_wishesLeft, 1);
    }

    Console::printLn(tr("You have {} wishes left", _wishesLeft));

    if (_wishesLeft <= 0)
    {
        Console::printLn(tr("This is it, you habe no wishes left. {} will leave you forever. Your {} is now a "
                            "worthless piece of junk.",
                            _djinn->name(),
                            WonderLamp::wonderlamp()));
        destroy();
    }
}

void CWonderLamp::destroy()
{
    _wasted = true;
    _isUsableFromInventory = false;
    _isUsableFromBattle = false;
    _isSellable = true;
    _description = tr("An old, rusy lamp. This one is junk.");
}

bool CWonderLamp::needsCleaning()
{
    const auto decay = CGameManagement::now() - _lastCaredFor;
    return decay > 25;
}

void CWonderLamp::spendTimeInside()
{
    Console::printLn(
        tr("You spend sone time together with {0} inside the {1}. {0} is a wonderful host, offers you a drink and some "
           "food. the {1} is a spacial place full of magic and mysteries, and {0} shows you some of them."));
    Console::printLn(
        tr("You spend your time chatting and laughing and enjoying yourselfs. You need to repeat that soon."));
    _djinn->addSympathy(Randomizer::getRandom(5) + 3);
    Console::br();
    Console::confirmToContinue();
}

void CWonderLamp::playGuessTheNumber()
{
    const auto playerGuesses = Randomizer::getRandomEntry<bool>({true, false});

    Console::printLn(tr("You decide to play a game of \"Guess the number\"."));
    if (playerGuesses)
    {
        Console::printLn(tr("A fun little game, where {} thinks of a number and you have to guess it."));
        Console::printLn(
            tr("Who knows, maybe after hanging out with {}, you learnd some mind-reading tricks.", _djinn->name()));
        Console::br();
        Console::printLn(tr("Guess a number between 1-10:"));
    }
    else
    {
        Console::printLn(tr("A fun little game, where you think of a number and {} has to guess it."));
        Console::printLn(tr("Playing mind-reading games agains a mind-reading Djinn, what could go wrong?"));
        Console::br();
        Console::printLn(tr("Select a number between 1-10 to think of:"));
    }
    auto input = Console::getNumberInputWithEcho(1, 10);

    if (!input.has_value())
    {
        Console::printLn(tr("This is too weird. Playing aginst a mind-reader is dumb. You forfeit and quit the game."));
        Console::printLn(tr("{} looks disapointed."));
        _djinn->addSympathy((Randomizer::getRandom(10) * -1) - 5);
        Console::br();
        Console::confirmToContinue();
        return;
    }

    bool magicOutcome = playerGuesses ? Randomizer::getRandom(10) == 0 : Randomizer::getRandom(2) == 0;
    const unsigned int firstNumber = input.value();
    const auto otherNumber = Randomizer::getRandom(9) + 1;

    if (playerGuesses)
    {
        if (magicOutcome)
        {
            Console::printLn(tr("Just before you want to say your number, you feel a magical ispriration."));
            if (firstNumber == otherNumber)
            {
                Console::printLn(
                    tr("You now know, that you guessed right, and full of confidence you state your number: {}.",
                       otherNumber));
            }
            else
            {
                Console::printLn(
                    tr("You know the number, and full of confidence you state your number: {}.", otherNumber));
            }
            Console::printLn(tr("{} is really impressed.", _djinn->name()));
            _djinn->addSympathy(Randomizer::getRandom(20) + 5);
        }
        else
        {
            Console::printLn(tr("You state your number: {}.", firstNumber));
            Console::printLn(tr("{} choose: {}.", _djinn->name(), otherNumber));

            if (firstNumber == otherNumber)
            {
                Console::printLn(tr("{}You guessed right!{}", CC::fgYellow(), CC::ccReset()));
                Console::printLn(tr("Probably a lucky break, but {} looks surprised,", _djinn->name()));
                _djinn->addSympathy(Randomizer::getRandom(5) + 5);
            }
            else
            {
                Console::printLn(tr("{}You guessed wrong!{}", CC::fgRed(), CC::ccReset()));
                Console::printLn(tr("{} does not look surprised,", _djinn->name()));
                _djinn->addSympathy(Randomizer::getRandom(5) + 5);
            }
        }
    }
    else
    {
        if (magicOutcome)
        {
            Console::printLn(
                tr("Before you even state your number, {} says: {}, {} eyes looking deeply into your mind.",
                   _djinn->name(),
                   firstNumber,
                   _djinn->hisHer()));
            Console::printLn(tr("Turns out, you are just a mere human, and should not play mind-reading games with a "
                                "mind-reader. Or should you?"));
            Console::printLn(tr("Nevertheless, {} looks a little disapointed.", _djinn->name()));
            _djinn->addSympathy(-1);
        }
        else
        {
            Console::printLn(tr("{} states {} number: {}.", _djinn->name(), _djinn->hisHer(), otherNumber));
            Console::printLn(tr("You choose: {}.", _djinn->name(), firstNumber));

            if (firstNumber == otherNumber)
            {
                Console::printLn(tr("{}{} guessed right!{}", CC::fgRed(), _djinn->name(), CC::ccReset()));
                Console::printLn(tr("Anyway, {} looks surprised, you shielded your mind better, than {} thought",
                                    _djinn->name(),
                                    _djinn->heShe()));
                _djinn->addSympathy(Randomizer::getRandom(5) + 5);
            }
            else
            {
                Console::printLn(tr("{}{} guessed wrong!{}", CC::fgYellow(), _djinn->name(), CC::ccReset()));
                Console::printLn(
                    tr("{} does not look surprised and impressed, {} had no chance to read your mind", _djinn->name()));
                _djinn->addSympathy(Randomizer::getRandom(10) + 5);
            }
        }
    }
    Console::br();
    Console::confirmToContinue();
}

void CWonderLamp::playLudo()
{
    Console::printLn(
        tr("You decide to play a game of Ludo with {}. Tt is a relaxing match, it is fun and it is a little exciting.",
           _djinn->name()));

    const auto outcome = Randomizer::getRandom(9);

    if (outcome == 0)
    {
        Console::printLn(tr("Until it isnt. When the tides turn towards {0}s side, you start to get angry. Eventually "
                            "you lose it all and before the game even ends, you throw over the board, throw around the "
                            "game pieces and rant towards {0}.",
                            _djinn->name()));
        Console::printLn(
            tr("Losing is surely not one of the core-competencies of a big strong hero. What a baby you are!"));
        _djinn->addSympathy((Randomizer::getRandom(25) * -1) - 5);
    }
    else if (outcome == 1)
    {
        Console::printLn(
            tr("Until it isnt. When the tides turn towards your side, {0} starts to get angry. Eventually "
               "{1} losees it all and before the game even ends, {1} throws over the board, throws around the "
               "game pieces and screams towards you.",
               _djinn->name(),
               _djinn->heShe()));
        Console::printLn(
            tr("Losing is surely not one of the core-competencies of a _djinn. What a baby {} is!", _djinn->heShe()));
        _djinn->addSympathy((Randomizer::getRandom(25) * -1) - 5);
    }
    else if (outcome > 1)
    {
        Console::printLn(tr("In the end, it was really enjoyable for both of you"));
        if (outcome <= 5)
        {
            Console::printLn(tr("More for {} though, {} wins the game.", _djinn->name(), _djinn->heShe()));
        }
        else
        {
            Console::printLn(tr("More for you though, you win the game."));
        }
        _djinn->addSympathy(Randomizer::getRandom(10) + 5);
    }
    Console::printLn("you should consider to play again.");
    Console::br();
    Console::confirmToContinue();
}

void CWonderLamp::playCards()
{
    Console::printLn(
        tr("You and {} spend some time and play a cozy game of cards. While playing you are chatting, laughing, "
           "having fun. just some nice, cozy quality time together.",
           _djinn->name()));
    _djinn->addSympathy(Randomizer::getRandom(5) + 1);
    Console::br();
    Console::confirmToContinue();
}
