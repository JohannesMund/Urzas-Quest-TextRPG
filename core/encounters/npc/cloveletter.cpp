#include "cloveletter.h"

#include "cgamemanagement.h"
#include "cmenu.h"
#include "cnpc.h"
#include "colorize.h"
#include "console.h"
#include "randomizer.h"

CLoveLetter::CLoveLetter()
{
    _isSingleExecution = false;
    _type = CEncounter::eField;
}

void CLoveLetter::execute(const std::string_view& moduleName)
{
    CEncounter::execute(moduleName);
    _hasBeenExecuted = true;

    auto significantOther = CGameManagement::getPlayerInstance()->signigicantOther();

    if (significantOther == nullptr)
    {
        Console::printLn(coreTr("Wandering around, having adventures, beeing a brave and strong hero, you see some "
                                "pigeons. You cannot help to think about roasted pigeons. you are hungry."));
        return;
    }

    const auto pigeon = coreTr("{}pigeon{}", CC::fgWhite(), CC::ccReset());

    Console::printLn(coreTr("Wandering around, having adventures, beeing a brave and strong hero, you cannot help to "
                            "think about {} more and more often. You have seen each other for {} now.",
                            significantOther->name(),
                            significantOther->notSeenString()));
    Console::printLn(
        coreTr("You miss {0} and really would love to hear from {0}. While re-planning your travel route, "
               "to visit {1} again as soon as possible, a {2} lands before you, and this pigeon carries a message.",
               significantOther->himHer(),
               significantOther->name(),
               pigeon));

    Console::printLn(coreTr("This message is from {0} for you, you are happy to hear from {1}. {2} writes, that {2} "
                            "loves you and misses you, and you feel the same.",
                            significantOther->name(),
                            significantOther->himHer(),
                            significantOther->heShe()));

    Console::br();
    Console::printLn(
        coreTr("The {} is still there. You could write and answer now and send it back to {}. {} surely deserves an "
               "answer. But an answer takes time and you are still a brave, strong and above all busy hero.",
               pigeon,
               significantOther->name(),
               significantOther->heShe()));

    CMenu menu(moduleName);
    const auto replyAction = menu.createAction({"Reply", 'R'});
    const auto goAction = menu.createAction({"Go away", 'G'});

    menu.addMenuGroup({replyAction}, {goAction});
    const auto input = menu.execute();

    Console::br();
    if (input == replyAction)
    {
        Console::printLn(coreTr("Brave and strong hero or not, {} took the time tom write you a letter and you will "
                                "take a time to reply to the letter. {} is your {} after all.",
                                significantOther->name(),
                                significantOther->heShe(),
                                significantOther->girlfriendBoyfriend()));
        Console::printLn(coreTr("You take your time, and write an emotianal letter to {0}, expressing your feelings "
                                "for {1} and telling {1}, how much you miss {1}.",
                                significantOther->name(),
                                significantOther->himHer()));
        Console::printLn(coreTr(
            "The {} is still waiting. You hand over your letter and send it to {}.", pigeon, significantOther->name()));

        const auto sympathy = 10 + Randomizer::getRandom(40);
        if (sympathy > 40)
        {
            Console::printLn("Writing this letter felt awesomne, your letter surely hit the spot.");
        }

        significantOther->reconcile(sympathy);
    }
    else
    {
        Console::printLn(coreTr("It was nice to hear from {}. Sure, you are missing {} too, but the whole letter felt "
                                "a little like \"overly attached {}.\"",
                                significantOther->name(),
                                significantOther->himHer(),
                                significantOther->girlfriendBoyfriend()));
        Console::printLn(coreTr("You will visit {} again soon enough, but now it is time for serious hero business. "
                                "Zhe {} flies away without a letter after a while and looks a little sad.",
                                significantOther->himHer(),
                                pigeon));
        significantOther->estrange(25);
    }
}

unsigned int CLoveLetter::encounterChance(const EEncounterType&, const std::string_view&) const
{
    if (CGameManagement::getPlayerInstance()->hasSignificantOther())
    {
        const auto turnsNotSeen = CGameManagement::getPlayerInstance()->signigicantOther()->turnsNotSeen();
        if (turnsNotSeen > 100)
        {
            return 10;
        }
        if (turnsNotSeen > 50)
        {
            return 5;
        }
        return 3;
    }
    return 0;
}

std::string CLoveLetter::name() const
{
    return coreTr("Love Pigeon");
}

std::string CLoveLetter::translatorModuleName() const
{
    return std::string();
}

std::string CLoveLetter::translatorObjectName() const
{
    return std::string(TagNames::Translator::loveLetter);
}
