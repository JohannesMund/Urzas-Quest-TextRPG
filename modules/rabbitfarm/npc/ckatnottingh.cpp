#include "ckatnottingh.h"
#include "cappleinteraction.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "core.h"
#include "rabbitfarm/encounters/cappletree.h"
#include "rabbitfarm/items/capple.h"
#include "rabbitfarm/moduleressources.h"
#include "randomizer.h"

CKatNottingH::CKatNottingH() : CNpc(TagNames::RabbitFarm::kat, Core::EGender::eFemale)
{
    addInteraction(new CAppleInteraction(this));
}

void CKatNottingH::interact()
{
    CNpc::interact();
    CMenuAction input;
    do
    {
        printHeader();
        CMenu menu(RabbitFarm::moduleName());
        input = CNpc::executeNpcMenu(menu);

    } while (input != CMenu::exit());
}

void CKatNottingH::talk()
{
    if (isSignificantOther())
    {
        Console::printLn(
            tr("it is always a pleasure to spend time with {0} at the {1} it feels like home for you, {0} "
               "feels like home for you. You talk about your adventures, rabbits, the {1} and all the rest.",
               RabbitFarm::katNottingH(),
               RabbitFarm::rabbitHatchName()));
        Console::printLn(tr("You spend a beautiful day at the {}, but your adventures are calling. A kingdom does not "
                            "save itelf. You feel sad as you have to leave, but for sure, you will bring the most "
                            "beautiful {} you can find, the next time you visit {}. The sooner the better.",
                            RabbitFarm::rabbitHatchName(),
                            RabbitFarm::apple(),
                            RabbitFarm::katNottingH()));
        addSympathy(10);
    }

    switch (sympathy())
    {
    case CNpc::ESympathyLevel::eNeutral:
    default:
        Console::printLn(
            tr("{0} and you have a nice, long talk. You talk about rabbits, and the {1}, what it means to care for all "
               "those little rabbits. You enjoy {0}s company. She is a nice lady, with an engaging personality. And "
               "she's pretty. Really pretty.",
               RabbitFarm::katNottingH(),
               RabbitFarm::rabbitHatchName()));
        Console::printLn(tr("Turns out, she likes {}s a lot. Maybe you can get her some?", RabbitFarm::apple()));
        break;

    case CNpc::ESympathyLevel::eLike:
        Console::printLn(
            tr("You like beeing in the {1} and you like beeing with {0}. You never liked her glasses too much, but the "
               "more you are talking, the more you realize the beatiful eyes behind the glasses. You talk about "
               "everything and nothing, it does not seem to matter, what matters more, is beeing together with her. "
               "The more you talk, the more beautiful {0} becomes.",
               RabbitFarm::katNottingH(),
               RabbitFarm::rabbitHatchName()));
        Console::printLn(tr("You relly have to get some {}s for her", RabbitFarm::apple()));

        break;
    case CNpc::ESympathyLevel::eLove:
        Console::printLn(tr(
            "{}, beautiful and nice. {} hits your life like a bombshell. You talk for a long time. you listen to every "
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
                "You catch yourself think about asking her out for a date, but {} will probably not like that too much",
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
    if (_sympathy > 60)
    {
        return tr("{} is a friendly, really beautiful lady. She is an extraordinaryly {} woman. She has beautiful eyes "
                  "and a breathtaking smile. She is smart and funny. You "
                  "could spend hoours and hours listening to her. Sometimes, you even wish you where a rabbit.",
                  RabbitFarm::katNottingH(),
                  RabbitFarm::coolAndStrong());
    }

    if (_sympathy < 40)
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

nlohmann::json CKatNottingH::save() const
{
    nlohmann::json o = CNpc::save();
    return o;
}

void CKatNottingH::load(const nlohmann::json& json)
{
    CNpc::load(json);
}

std::string CKatNottingH::translatorModuleName() const
{
    return RabbitFarm::moduleName();
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
