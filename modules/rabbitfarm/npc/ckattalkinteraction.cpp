
#include "ckattalkinteraction.h"
#include "cgamemanagement.h"
#include "cnpc.h"
#include "console.h"
#include "rabbitfarm/moduleressources.h"

CKatTalkInteraction::CKatTalkInteraction(CNpc* npc) :
    CTalkInteraction(npc, TagNames::RabbitFarm::talkInteraction),
    _cooldown(25)
{
}

void CKatTalkInteraction::executeInteraction()
{
    CNpcInteraction::executeInteraction();
    if (_npc->isSignificantOther())
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
        _npc->addSympathy(10);
    }

    switch (_npc->sympathy())
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
    if (_npc->isDatable())
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

std::string CKatTalkInteraction::translatorModuleName() const
{
    return RabbitFarm::moduleName();
}