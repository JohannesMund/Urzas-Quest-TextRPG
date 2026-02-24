#include "ckatnottingh.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "rabbitfarm/encounters/cappletree.h"
#include "rabbitfarm/items/capple.h"
#include "rabbitfarm/moduleressources.h"
#include "randomizer.h"

CKatNottingH::CKatNottingH() : CNpc(TagNames::RabbitFarm::kat, true)
{
}

void CKatNottingH::interact()
{
    CNpc::interact();
    CMenuAction input;
    do
    {
        printHeader();

        CMenu menu(RabbitFarm::moduleName());
        auto appleAction = menu.createAction({"Give her an Apple", 'G'});

        CMenu::ActionList katList;
        if (CGameManagement::getInventoryInstance()->hasItem(CApple::aopleFilter()))
        {
            katList.push_back(appleAction);
        }

        menu.addMenuGroup(katList);
        input = CNpc::executeNpcMenu(menu);

        if (input == appleAction)
        {
            giveApple();
            Console::confirmToContinue();
        }
    } while (input != CMenu::exit());
}

void CKatNottingH::talk()
{
    registerAppleEncounter();

    if (isSignificantOther())
    {
        Console::printLn(tr("it is always a pleasure to spend time with {0} at the {1} it feels like home for you, {0} "
                            "feels like home for you. You talk about your adventures, the {1} and all the rest.",
                            RabbitFarm::katNottingH(),
                            RabbitFarm::rabbitHatchName()));
        Console::printLn(
            tr("While admiring her {} are the best, and for sure, you need to get a extraordinary beautiful {} "
               "for your next visit. Also, another date would be great, don't you think?",
               RabbitFarm::katsBoots(),
               RabbitFarm::apple()));
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
               RabbitFarm::katNottingH(),
               RabbitFarm::rabbitHatchName()));
        Console::printLn(tr("Turns out, she likes {}s a lot. Maybe you can get her some?", RabbitFarm::apple()));
        break;

    case CNpc::ESympathyLevel::eLike:
        Console::printLn(
            tr("You like beeing in the {1} and you like beeing with {0}. You never liked her glasses too much, but the "
               "more you are talking, the more you realize the beatiful eys behind the glasses. You talk about "
               "everything and nothing, it does not seem to matter, what matters more, is beeing together with her. "
               "The more you talk, the more beautiful {0} becomes.",
               RabbitFarm::katNottingH(),
               RabbitFarm::rabbitHatchName()));
        Console::printLn(tr("You relly have to get some {}s for her", RabbitFarm::apple()));

        break;
    case CNpc::ESympathyLevel::eLove:
        Console::printLn(tr(
            "{}, beautiful and nice. {} hit your life like a bombshell. You talk for a long time. you listen to every "
            "word she says. you enjoy her smile, every even so small contact. You simply enjoy beeing with her.",
            RabbitFarm::coolAndStrong(),
            RabbitFarm::katNottingH()));
        Console::printLn(
            tr("One thing is for sure, you have to get her the sweetest, most juicy, most beautiful {0} "
               "you can find. Even though you are very sure, that you will not find an {0} to match her beauty",
               RabbitFarm::apple()));
        break;
    case CNpc::ESympathyLevel::eDislike:
        Console::printLn(tr("{}, the rabbit lady. Whats her point with all those rabbits? In the end, there is nit "
                            "much you can take away from this talk, only one thing: This woman is obsessed with {}s",
                            RabbitFarm::katNottingH(),
                            RabbitFarm::apple()));
        break;
    case CNpc::ESympathyLevel::eHate:
        Console::printLn(tr("All you can think of right now, is rabbit roast, but for sure, this hag will hav "
                            "something against it. Maybe she will trade of those rabbits for an {}?",
                            RabbitFarm::apple()));
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
    Console::br();
}

std::string CKatNottingH::name() const
{
    return RabbitFarm::katNottingH();
}

std::string CKatNottingH::describe() const
{
    if (_sympathy > 75)
    {
        return tr("{} s a friendly, really beautiful lady. She is an extraordinaryly {} woman. She has beautiful eyes "
                  "and a breathtaking smile. She is smart and funny. You "
                  "could spend hoours and hours listening to her. Sometimes, you even wish you where a rabbit.",
                  RabbitFarm::katNottingH(),
                  RabbitFarm::coolAndStrong());
    }

    if (_sympathy > 75)
    {
        return tr("{} is a nice woman, she is {}, but her job as Head of the {} also adds some "
                  "eco-hippie flare. You do not like her glasses.",
                  RabbitFarm::katNottingH(),
                  RabbitFarm::coolAndStrong(),
                  RabbitFarm::rabbitHatchName());
    }

    return tr("{} s a friendly, pretty lady. she has a friendly, warm smile and seem to be an extraordinary {} woman. "
              "She is Head of the {} so, obviously, she likes Rabbits. and damn, she is really "
              "pretty! Her {} are uber-cool",
              RabbitFarm::katNottingH(),
              RabbitFarm::coolAndStrong(),
              RabbitFarm::rabbitHatchName(),
              RabbitFarm::katsBoots());
}

CMenuAction CKatNottingH::npcNav(CMenu& menu) const
{
    return menu.createAction({CC::unColorizeString(RabbitFarm::katNottingH())});
}

nlohmann::json CKatNottingH::save() const
{
    nlohmann::json o;
    o["appleEncounterRegistered"] = _appleEncounterRegistered;
    return o;
}

void CKatNottingH::load(const nlohmann::json& json)
{
    if (json["appleEncounterRegistered"] == true)
    {
        registerAppleEncounter();
    }
}

std::string CKatNottingH::translatorModuleName() const
{
    return RabbitFarm::moduleName();
}

void CKatNottingH::registerAppleEncounter()
{
    if (!_appleEncounterRegistered)
    {
        CGameManagement::getInstance()->registerEncounter(new CAppleTree(this));
        _appleEncounterRegistered = true;
    }
}

void CKatNottingH::giveApple()
{
    auto apples = CGameManagement::getInventoryInstance()->getItemsByFilter(CApple::aopleFilter());
    if (!apples.size())
    {
        Console::printLn(tr("Well, this is emberrassing. You search your bag for {}s, but apperently you have none.",
                            RabbitFarm::apple()));
        Console::printLn(tr("{} looks dissapointed.", RabbitFarm::katNottingH()));
        return;
    }
    auto oneApple = apples.at(0);
    CGameManagement::getInventoryInstance()->removeItem(oneApple);

    auto sympathy = 10 + Randomizer::getRandom(40);
    if (sympathy > 45)
    {
        Console::printLn(
            tr("{}s Eyes are gleaming, when she sees you {}. This must be the most beautiful apple she has ever seen",
               RabbitFarm::katNottingH(),
               RabbitFarm::apple()));
    }
    else if (sympathy > 25)
    {
        Console::printLn(tr("{0} seems to like your {1}. You think, this is a beautiful {1}.",
                            RabbitFarm::katNottingH(),
                            RabbitFarm::apple()));
    }
    else
    {
        Console::printLn(tr(
            "{0} thanks you politely, and puts your {1} to her other {1}s. It is the gesture that counts, you guess.",
            RabbitFarm::katNottingH(),
            RabbitFarm::apple()));
    }

    addSympathy(sympathy);
    Console::br();
}

void CKatNottingH::printHeader(const bool bFull) const
{
    Console::cls();
    Console::printLn(RabbitFarm::katNottingH(), Console::EAlignment::eCenter);
    if (bFull)
    {
        Console::br();
        Console::printLn(describe(), Console::EAlignment::eCenter);
    }
    Console::br();
}
