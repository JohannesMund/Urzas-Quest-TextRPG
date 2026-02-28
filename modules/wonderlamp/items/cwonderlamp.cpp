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
}

void CWonderLamp::replaceGem()
{
    if (!CGameManagement::getInventoryInstance()->hasItem(CGem::gemFilter()))
    {
        Console::printLn(tr("You dont have a gem. maybe later."));
        return;
    }

    auto gem = CGameManagement::getInventoryInstance()->getFirstItemByFilter<CGem>(CGem::gemFilter());
    if (!gem.has_value())
    {
        Console::printLn(tr("You dont have a gem. maybe later."));
        return;
    }

    Console::printLn(tr("There is a gap on your {} where the gem fell of. You decide to replace it with a beautiful "
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
