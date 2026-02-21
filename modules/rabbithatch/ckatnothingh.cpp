#include "ckatnothingh.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "rabbithatch/encounters/crabbithatchappletree.h"
#include "rabbithatch/items/crabbithatchapple.h"
#include "rabbithatch/moduleressources.h"
#include "randomizer.h"

CKatNothingH::CKatNothingH() : CNpc(TagNames::RabbitHatch::kat, true)
{
}

void CKatNothingH::interact()
{
    CNpc::interact();
    CMenuAction input;
    do
    {
        printHeader();

        CMenu menu(RabbitHatch::moduleName());
        auto appleAction = menu.createAction({"Give her an Apple", 'G'});

        CMenu::ActionList katList;
        if (CGameManagement::getInventoryInstance()->hasItem(CRabbithatchApple::aopleFilter()))
        {
            katList.push_back(appleAction);
        }

        menu.addMenuGroup(katList, {CMenu::exit()});
        input = CNpc::executeNpcMenu(menu);

        if (input == appleAction)
        {
            giveApple();
        }

        if (input != CMenu::exit())
        {
            Console::br();
            Console::confirmToContinue();
        }

    } while (input != CMenu::exit());
}

void CKatNothingH::talk()
{
    registerAppleEncounter();

    if (isSignificantOther())
    {
        Console::printLn(tr("it is always a pleasure to spend time with {0} at the {1} it feels like home for you, {0} "
                            "feels like home for you. You talk about your adventures, the {1} and all the rest.",
                            RabbitHatch::katNothingH(),
                            RabbitHatch::rabbitHatchName()));
        Console::printLn(
            tr("While admiring her {} are the best, and for sure, you need to get a extraordinary beautiful {} "
               "for your next visit. Also, another date would be great, don't you think?",
               RabbitHatch::katsBoots(),
               RabbitHatch::apple()));
        addSympathy(10);
    }

    switch (sympathy())
    {
    case CNpc::ESympathyLevel::eNeutral:
    default:
        Console::printLn(
            tr("{0} and you have a nice, long talk. You talk about rabbits, and the {1}, what it means to care for all "
               "those little rabbits. You enjoy {0}s company. She is a nice lady, with an engaging personality. And "
               "she's pretty. Peally pretty.",
               RabbitHatch::katNothingH(),
               RabbitHatch::rabbitHatchName()));
        Console::printLn(tr("Turns out, she likes {}s a lot. Maybe you can get her some?", RabbitHatch::apple()));
        break;

    case CNpc::ESympathyLevel::eLike:
        Console::printLn(
            tr("You like beeing in the {1} and you like beeing with {0}. You never liked her glasses too much, but the "
               "more you are talking, the more you realize the beatiful eys behind the glasses. You talk about "
               "everything and nothing, it does not seem to matter, what matters more, is beeing together with her. "
               "The more you talk, the more beautiful {0} becomes.",
               RabbitHatch::katNothingH(),
               RabbitHatch::rabbitHatchName()));
        Console::printLn(tr("You relly have to get some {}s for her", RabbitHatch::apple()));

        break;
    case CNpc::ESympathyLevel::eLove:
        Console::printLn(tr(
            "{}, beautiful and nice. {} hit your life like a bombshell. You talk for a long time. you listen to every "
            "word she says. you enjoy her smile, every even so small contact. You simply enjoy beeing with her.",
            RabbitHatch::coolAndStrong(),
            RabbitHatch::katNothingH()));
        Console::printLn(
            tr("One thing is for sure, you have to get her the sweetest, most juicy, most beautiful {0} "
               "you can find. Even though you are very sure, that you will not find an {0} to match her beauty",
               RabbitHatch::apple()));
        break;
    case CNpc::ESympathyLevel::eDislike:
        Console::printLn(tr("{}, the rabbit lady. Whats her point with all those rabbits? In the end, there is nit "
                            "much you can take away from this talk, only one thing: This woman is obsessed with {}s",
                            RabbitHatch::katNothingH(),
                            RabbitHatch::apple()));
        break;
    case CNpc::ESympathyLevel::ehate:
        Console::printLn(tr("All you can think of right now, is rabbit roast, but for sure, this hag will hav "
                            "something against it. Maybe she will trade of those rabbits for an {}?",
                            RabbitHatch::apple()));
        break;
    }
    if (isDatable())
    {
        if (CGameManagement::getPlayerInstance()->hasSignificantOther())
        {
            Console::printLn(tr(
                "You catch yourself think about asking her outfor a date, but {} will probably not like that too much",
                CGameManagement::getPlayerInstance()->signigicantOther()->name()));
        }
        else
        {
            Console::printLn(tr("You really should ask her out for a date someday"));
        }
    }
}

std::string CKatNothingH::name() const
{
    return RabbitHatch::katNothingH();
}

std::string CKatNothingH::describe() const
{
    if (_sympathy > 75)
    {
        return tr("{} s a friendly, really beautiful lady. She is an extraordinaryly {} woman. She has beautiful eyes "
                  "and a breathtaking smile. She is smart and funny. You "
                  "could spend hoours and hours listening to her. Sometimes, you even wish you where a rabbit.",
                  RabbitHatch::katNothingH(),
                  RabbitHatch::coolAndStrong());
    }

    if (_sympathy > 75)
    {
        return tr("{} is a nice woman, she is {}, but her job as Head of the {} also adds some "
                  "eco-hippie flare. You do not like her glasses.",
                  RabbitHatch::katNothingH(),
                  RabbitHatch::coolAndStrong(),
                  RabbitHatch::rabbitHatchName());
    }

    return tr("{} s a friendly, pretty lady. she has a friendly, warm smile and seem to be an extraordinary {} woman. "
              "She is Head of the {} so, obviously, she likes Rabbits. and damn, she is really "
              "pretty! Her {} are uber-cool",
              RabbitHatch::katNothingH(),
              RabbitHatch::coolAndStrong(),
              RabbitHatch::rabbitHatchName(),
              RabbitHatch::katsBoots());
}

nlohmann::json CKatNothingH::save() const
{
    nlohmann::json o;
    o["appleEncounterRegistered"] = _appleEncounterRegistered;
    return o;
}

void CKatNothingH::load(const nlohmann::json& json)
{
    if (json["appleEncounterRegistered"] == true)
    {
        registerAppleEncounter();
    }
}

std::string CKatNothingH::translatorModuleName() const
{
    return RabbitHatch::moduleName();
}

void CKatNothingH::registerAppleEncounter()
{
    if (!_appleEncounterRegistered)
    {
        CGameManagement::getInstance()->registerEncounter(new CRabbitHatchAppleTree(this));
        _appleEncounterRegistered = true;
    }
}

void CKatNothingH::giveApple()
{
    auto apples = CGameManagement::getInventoryInstance()->getItemsByFilter(CRabbithatchApple::aopleFilter());
    if (!apples.size())
    {
        Console::printLn(tr("Well, this is emberrassing. You search your bag for {}s, but apperently you have none.",
                            RabbitHatch::apple()));
        Console::printLn(tr("{} looks dissapointed.", RabbitHatch::katNothingH()));
        return;
    }
    auto oneApple = apples.at(0);
    CGameManagement::getInventoryInstance()->removeItem(oneApple);

    auto sympathy = 10 + Randomizer::getRandom(40);
    if (sympathy > 45)
    {
        Console::printLn(
            tr("{}s Eyes are gleaming, when she sees you {}. This must be the most beautiful apple she has ever seen",
               RabbitHatch::katNothingH(),
               RabbitHatch::apple()));
    }
    else if (sympathy > 25)
    {
        Console::printLn(tr("{0} seems to like your {1}. You think, this is a beautiful {1}.",
                            RabbitHatch::katNothingH(),
                            RabbitHatch::apple()));
    }
    else
    {
        Console::printLn(tr(
            "{0} thanks you politely, and puts your {1} to her other {1}s. It is the gesture that counts, you guess.",
            RabbitHatch::katNothingH(),
            RabbitHatch::apple()));
    }

    addSympathy(sympathy);
}

void CKatNothingH::printHeader(const bool bFull) const
{
    Console::cls();
    Console::printLn(RabbitHatch::katNothingH(), Console::EAlignment::eCenter);
    if (bFull)
    {
        Console::printLn(describe(), Console::EAlignment::eCenter);
    }
    Console::br();
}
