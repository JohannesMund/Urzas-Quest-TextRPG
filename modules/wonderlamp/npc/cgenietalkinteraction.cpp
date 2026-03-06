#include "cgenietalkinteraction.h"

#include "cgamemanagement.h"
#include "cnpc.h"
#include "console.h"
#include "wonderlamp/moduleressources.h"

CGenieTalkInteraction::CGenieTalkInteraction(CNpc* npc) :
    CTalkInteraction(npc, TagNames::WonderLamp::genieTalkInteraction)
{
}

void CGenieTalkInteraction::executeInteraction()
{
    if (_npc->isSignificantOther())
    {
        Console::printLn(
            tr("If there is one major advantage in dating a djinn, than it would surely be the fact, that you have "
               "your boyfriend always with you. Just rub the {} whenever you feel like and {} appears.",
               WonderLamp::wonderlamp(),
               _npc->name()));
        Console::printLn(
            tr("{} invites you into his lamp and you spend your time chatting lauging and enjoying yourselfs. You "
               "realize again, how lucky you are, having such a magic and special boyfriend",
               _npc->name()));
        _npc->addSympathy(10);
    }

    switch (_npc->sympathy())
    {
    case CNpc::ESympathyLevel::eNeutral:
    default:
        Console::printLn(tr("{0} is really magic and your are very interested to learn more about him and about djinns "
                            "in general. He tells you a lot about the djinn society, the rules, the magic and all the "
                            "resst. you are intrigued and fascinated by this man and the djinns.",
                            _npc->name()));
        Console::printLn(tr("Turns out, djinns like gems a lot. Maybe you can get him some?"));
        break;

    case CNpc::ESympathyLevel::eLike:
        Console::printLn(tr("You like beeing with {}. He is a fascinating, magically beeing. And he is "
                            "extraordinarily handsome. He has a lot to say and you love to hear all of it. He is "
                            "also interested in your adventures and your live as a strong and brave hero. From time to "
                            "time he even asks you to visit her in his {}. ",
                            _npc->name(),
                            WonderLamp::wonderlamp()));
        Console::printLn(tr("You really have to get some gemss for him"));

        break;
    case CNpc::ESympathyLevel::eLove:
        Console::printLn(tr("{} is the most fascinating beeing you ever met in your live. He is magical and "
                            "handsome, but above all, it is always a fun enjoyable time you spend together. Lately you "
                            "are visiting him regularily in his bottle.",
                            _npc->name()));
        Console::printLn(tr("You feel the urge to find the best, and biggest and cleares gems for him."));
        break;
    case CNpc::ESympathyLevel::eDislike:
        Console::printLn(tr("{}, The djinn dude. You don't have much to talk about. Usually he repeats the rules, and "
                            "emphazises, that once the wishes are used up, he will be gone.",
                            _npc->name()));
        break;
    case CNpc::ESympathyLevel::eHate:
        Console::printLn(tr("All {} has to say is, that there is only 1 wish left until he leaves.", _npc->name()));
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

std::string CGenieTalkInteraction::translatorModuleName() const
{
    return WonderLamp::moduleName();
}
