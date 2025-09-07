#include "cshrineoftheancients.h"
#include "cequipment.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "moduleressources.h"
#include "ressources.h"

#include <format>
CShrineOfTheAncients::CShrineOfTheAncients() : CRoom("CShrineOfTheAnchients")
{
    _description = "";
    _encounterType = CEncounter::EEncounterType::eNone;
    _isRandomTaskPossible = false;
    _showInFogOfWar = true;
}

void CShrineOfTheAncients::execute()
{
    CRoom::execute();

    if (_seenDuringPhase != CGameManagement::getProgressionInstance()->currentGameStage())
    {
        firstVisit();
    }
    else
    {
        visit();
    }
    Console::br();
    CMenu menu;
    menu.addMenuGroup({menu.createAction("Think about yourself")}, {CMenu::exit()});
    if (menu.execute() == CMenu::exit())
    {
        return;
    }
    stats();
}

std::string CShrineOfTheAncients::fgColor() const
{
    return CC::fgDarkGray();
}

std::string CShrineOfTheAncients::bgColor() const
{
    return CC::bgLightGray();
}

void CShrineOfTheAncients::visit()
{
    Console::printLn(std::format("Once again, you approach the {}.", ancientShrine()));
    switch (CGameManagement::getProgressionInstance()->currentGameStage())
    {
    case CGameProgression::EGameStage::eNone:
    case CGameProgression::EGameStage::eStart:
    case CGameProgression::EGameStage::eSeenBard:
        Console::printLn("And as before, the old man does not even realize, that "
                         "you are there.");
        break;
    case CGameProgression::EGameStage::eProvenAsHero:
        Console::printLn("This time, the old man stands directly next to the "
                         "entry, and smiles at you. Obviousely, "
                         "your are still no hero.");
        break;
    case CGameProgression::EGameStage::eLearnedAboutCult:
    case CGameProgression::EGameStage::eFoundCult:
    case CGameProgression::EGameStage::eFoundUrza:
    case CGameProgression::EGameStage::eFinale:
        Console::printLn(
            "This time, grampa stands in the opened gate. He smiles, but you are probably still not ready.");
        break;
    }
}

void CShrineOfTheAncients::firstVisit()
{

    _seenDuringPhase = CGameManagement::getProgressionInstance()->currentGameStage();
    CGameManagement::getProgressionInstance()->reportModuleFinished(ShrineRessources::moduleName());

    switch (CGameManagement::getProgressionInstance()->currentGameStage())
    {
    case CGameProgression::EGameStage::eNone:
    case CGameProgression::EGameStage::eStart:
        firstVisitStart();
        break;
    case CGameProgression::EGameStage::eSeenBard:
        firstVisitSeenBard();
        break;
    case CGameProgression::EGameStage::eProvenAsHero:
        firstVisitProvenAsHero();
        break;
    case CGameProgression::EGameStage::eLearnedAboutCult:
        firstVisitLearnedAboutCult();
        break;
    case CGameProgression::EGameStage::eFoundCult:
    case CGameProgression::EGameStage::eFoundUrza:
    case CGameProgression::EGameStage::eFinale:
        Console::printLn("Not implemented");
        Console::confirmToContinue();
        break;
    }
}

void CShrineOfTheAncients::firstVisitStart()
{
    Console::printLn("There is something really strange before you. Something "
                     "like a shrine. A hoary shrine. This must "
                     "be a Shrine of the ancients.");
    Console::printLn("How you know? Surely because of your deep knowledget of "
                     "ancient religious history. And, of "
                     "course, the sign next to the gate reading:");
    Console::printLn(ancientShrine());
    Console::printLn("Do you want to have a look?");

    if (CMenu::executeYesNoMenu() == CMenu::no())
    {
        Console::printLn("You probably have seen enough, and leave this place.");
        return;
    }
    Console::printLn("You go closer, and can see an old man, praying in the shrine. He does "
                     "not even give you a single "
                     "glance, and completely ignores you. Well, time to leave for now.");
}

void CShrineOfTheAncients::firstVisitSeenBard()
{
    Console::printLn(std::format("As you apporach the {}, you see, something is "
                                 "different this time. The old man "
                                 "stands at the gate and looks at you.",
                                 ancientShrine()));
    Console::printLn("As you come closer, he asks, if you have any questions.");
    Console::printLn("What should you ask him?");
    Console::br();

    CMenu menu;
    CMenu::Action askAboutUrza = menu.createAction(Ressources::Game::whoTheFuckIsUrza(), 'w');
    menu.addMenuGroup({askAboutUrza}, {menu.createAction("Nothing")});
    if (menu.execute().key != 'w')
    {
        Console::printLn("\"No, not this time\", you think to yourself, and leave.");
    }
    Console::br();
    Console::printLn(std::format("You ask the question, that is lurkin around "
                                 "your head for so long now: {}?",
                                 Ressources::Game::whoTheFuckIsUrza()));
    Console::printLn(
        std::format("The old man smiles, and replies: \"So, you want to know about {}?", Ressources::Game::urza()));
    Console::printLn("This is dangerous knowledge, nowadays. To get an answer to "
                     "this question, you first have to become a hero!\"");
    Console::printLn("This was the most underwhelming answer you have ever heard "
                     "in your live, since you asked the "
                     "beautiful farmers daughter to go for the dance when you "
                     "was 8 years old.");
    Console::printLn("But your wanted to become a hero anyway, so you will have "
                     "to come back later.");
}

void CShrineOfTheAncients::firstVisitProvenAsHero()
{
    Console::printLn(std::format("Back to the {}. This time, the old man seems "
                                 "to await you and smiles at you.",
                                 ancientShrine()));
    Console::printLn("As you come closer, he asks, if you have any questions.");
    Console::printLn("And you have only one question in you mind?");
    Console::br();

    CMenu menu;
    CMenu::Action askAboutUrza = menu.createAction(Ressources::Game::urzaWhoTheFuckIsUrza(), 'w');
    menu.addMenuGroup({askAboutUrza}, {menu.createAction("Nothing")});
    if (menu.execute().key != 'w')
    {
        Console::printLn("Maybe, proven to be a hero is enough.");
    }
    Console::br();
    Console::printLn(std::format("The old man smiles wisely, and replies: \"{0} "
                                 "was important, and {0} is important!",
                                 Ressources::Game::urza()));
    Console::printLn("Find the people, who still believe in Urza!\"");
    Console::printLn("And again, you are not much smarter than before, but you "
                     "know what to look for.");
}

void CShrineOfTheAncients::firstVisitLearnedAboutCult()
{
    Console::printLn(
        std::format("The old man stands in the opened gate to the {}. He awaits you, but he will not yet let you in.",
                    ancientShrine()));
    Console::printLn("He asks you about your search.");
    Console::printLn("Do you want to tell him??");
    Console::br();

    CMenu menu;
    menu.addMenuGroup({menu.createAction("Sure thing!")}, {menu.createAction("Not yet")});
    if (menu.execute().key != 's')
    {
        Console::printLn("Maybe next time.");
    }

    Console::printLn(std::format("You tell the old man about what you learned, about the chapel you found and about {} "
                                 "and {}. You skip the part with your new {}tattoo{}.",
                                 Ressources::Game::fiego(),
                                 Ressources::Game::brock(),
                                 CC::fgLightMagenta(),
                                 CC::ccReset()));
    Console::printLn(
        "When the old man hears about the two revolutionaries, his face brightens even more. \"Find them!\" he says.");
    Console::printLn("Thats it, not much, but again, you know what to do.");
}

void CShrineOfTheAncients::stats() const
{
    Console::cls();
    Console::printLn("You take some time to think about yourself:");
    Console::br();

    auto progress = CGameManagement::getProgressionInstance()->progress();
    std::string progressString = "[";

    unsigned int i = 0;
    while (i < progress)
    {
        progressString.append("#");
        i += 2;
    }
    while (i < 100)
    {
        progressString.append(".");
        i += 2;
    }

    progressString.append("]");

    Console::printLnWithSpacer("Progress:", progressString);
    Console::printLnWithSpacer("Body count:",
                               std::format("{}", CGameManagement::getProgressionInstance()->bodyCount()));
    Console::printLnWithSpacer("Genocides committed:",
                               std::format("{}", CGameManagement::getProgressionInstance()->genocideCount()));
    Console::printLnWithSpacer("Turns:", std::format("{}", CGameManagement::getProgressionInstance()->turns()));

    Console::br();
    auto equipment = CGameManagement::getInventoryInstance()->getEquipment();
    for (auto e : equipment)
    {
        Console::printLnWithSpacer(std::format("{}:", e->typeName()),
                                   std::format("{} (Level {})", e->name(), e->level()));
    }

    auto quests = CGameManagement::getProgressionInstance()->getQuestLog();
    if (quests.size())
    {
        Console::br();
        Console::hr();
        Console::printLn("You current Quests:");
        Console::br();

        for (const auto& q : quests)
        {
            Console::printLn(q);
        }
    }
    Console::br();
    Console::confirmToContinue();
}

char CShrineOfTheAncients::getMapSymbol() const
{
    return 'Q';
}

std::string CShrineOfTheAncients::ancientShrine() const
{
    return std::format("{}hoar{}y Shrin{}e of the {}Ancients{}",
                       CC::fgCyan(),
                       CC::fgBlue(),
                       CC::fgLightCyan(),
                       CC::fgLightBlue(),
                       CC::ccReset());
}
