#include "cjeannie.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "wonderlamp/moduleressources.h"

CJeannie::CJeannie() : CBasicDjinn(Core::EGender::eFemale)
{
}

void CJeannie::talk()
{
    if (isSignificantOther())
    {
        Console::printLn(
            tr("If there is one major advantage in dating a djinn, than it would surely be the fact, that you have "
               "your girlfried always with you. Just rub the {} whenever you feel like and {} appears.",
               WonderLamp::wonderlamp(),
               name()));
        Console::printLn(
            tr("{} invites you into her lamp and you spend your time chatting lauging and enjoying yourselfs. You "
               "realize again, how lucky you are, having such a magic and special girlfriend",
               name()));
        addSympathy(10);
    }

    switch (sympathy())
    {
    case CNpc::ESympathyLevel::eNeutral:
    default:
        Console::printLn(tr("{0} is really magic and your are very interested to learn more about her and about djinns "
                            "in general. She tells you a lot about the djinn society, the rules, the magic and all the "
                            "resst. you are intrigued and fascinated by this lady and the djinns.",
                            name()));
        Console::printLn(tr("Turns out, djinns like gems a lot. Maybe you can get her some?"));
        break;

    case CNpc::ESympathyLevel::eLike:
        Console::printLn(tr("You like beeing with {}. She is a fascinating, magically beeing. And she is "
                            "extraordinarily beautiful. She has a lot to say and you love to hear all of it. She is "
                            "also interested in your adventures and your live as a strong and brave hero. From time to "
                            "time she even asks you to visit her in her {}. ",
                            name(),
                            WonderLamp::wonderlamp()));
        Console::printLn(tr("You really have to get some gemss for her"));

        break;
    case CNpc::ESympathyLevel::eLove:
        Console::printLn(
            tr("{} is the most fascinating beeing you ever met in your live. She is magical and "
               "beautiful, but above all, it is always a fun enjoyable time you spend together. Lately you "
               "are visiting her regularily in her bottle.",
               name()));
        Console::printLn(tr("You feel the urge to find the best, and biggest and cleares gems for her."));
        break;
    case CNpc::ESympathyLevel::eDislike:
        Console::printLn(tr("{}, The djinn lady. You don't have much to talk about. Usually she repeats the rules, and "
                            "emphazises, that once the wishes are used up, she will be gone.",
                            name()));
        break;
    case CNpc::ESympathyLevel::eHate:
        Console::printLn(tr("All {} has to say is, that there is only 1 wish left until she leaves.", name()));
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

std::string CJeannie::name() const
{
    return std::string(WonderLamp::genie());
}

std::string CJeannie::describe() const
{
    if (_sympathy > 60)
    {
        return tr("{} is a lovely, mysterious woman. She has long blond hair, her clothes look like taken directly "
                  "from the fairy tales and leave nothing to the fantasy. This magical woman is extraordiarily "
                  "beautiful, her smile is breathtakeing and her laughter enchants you everytime you hear it.",
                  name());
    }

    if (_sympathy < 40)
    {
        return tr("{} exhales magic. But she is not human, and her cloths look slutty.", name());
    }

    return tr("{} is a mysterious, pretty woman. She looks like she directly escaped a fairy tale book. She radiates "
              "magic and sex-appeal",
              name());
}

std::string CJeannie::colorize(const std::string_view& s) const
{
    return WonderLamp::colorizeJeannie(s);
}
