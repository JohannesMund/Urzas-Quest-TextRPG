#include "cshrineoftheancients.h"
#include "cequipment.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorconsole.h"
#include "console.h"
#include "ressources.h"

#include <format>
CShrineOfTheAncients::CShrineOfTheAncients()
{
    _description = "";

    _encounterPossible = false;
    _taskPossible = false;

    _showInFogOfWar = true;
}

void CShrineOfTheAncients::execute()
{
    CField::execute();

    if (_seenDuringPhase != CGameManagement::getProgressionInstance()->currentGameStage())
    {
        firstVisit();
        return;
    }
    visit();
}

std::string CShrineOfTheAncients::mapSymbol() const
{
    return "§";
}

void CShrineOfTheAncients::visit()
{

    Console::printLn(std::format("Once again, you approach the {}.", ancientShrine()));
    switch (CGameManagement::getProgressionInstance()->currentGameStage())
    {
    case CGameProgression::EGameStage::eNone:
    case CGameProgression::EGameStage::eStart:
        Console::printLn("And as before, the old man does not even realize, that you are there.");
        break;
    case CGameProgression::EGameStage::eSeenBard:
        Console::printLn("This time, the old man stands directly next to the entry, and smiles at you. Obviousely, "
                         "your are still no hero.");

    case CGameProgression::EGameStage::eProvenAsHero:
    case CGameProgression::EGameStage::eLearnedAboutCult:
        break;
    }
    Console::br();

    CMenu menu;

    menu.addMenuGroup({menu.createAction("Think about yourself")}, {CMenu::exitAction()});

    if (CMenu::exit(menu.execute()))
    {
        return;
    }
    stats();
}

void CShrineOfTheAncients::firstVisit()
{
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
    case CGameProgression::EGameStage::eLearnedAboutCult:
        break;
    }
}

void CShrineOfTheAncients::firstVisitStart()
{
    Console::printLn("There is something really strange before you. Something like a shrine. A hoary shrine. This must "
                     "be a Shrine of the ancients.");
    Console::printLn("How you know? Surely because of your deep knowledget of ancient religious history. And, of "
                     "course, the signe next to the gate reading:");
    Console::printLn(ancientShrine());
    Console::printLn("Do you want to have a look?");

    if (CMenu::no(CMenu::executeYesNoMenu()))
    {
        Console::printLn("You probably have seen enough, and leave this place.");
        return;
    }

    Console::printLn("You go closer, and can see an old man, praying in the shrine. He does not even give you a single "
                     "glance, and completely ignores you. Well, time to leave for now.");

    CGameManagement::getProgressionInstance()->reportModuleFinished(Ressources::Game::ShrineRessources::moduleName());
    _seenDuringPhase = CGameManagement::getProgressionInstance()->currentGameStage();
}

void CShrineOfTheAncients::firstVisitSeenBard()
{
    Console::printLn(std::format("As you apporach the {}, you see, something is different this time. The old man "
                                 "stands at the gate and looks at you.",
                                 ancientShrine()));
    Console::printLn("As you come closer, he asks, if you have any questions.");
    Console::printLn("What should you ask him?");
    Console::br();

    CMenu menu;
    CMenu::Action askAboutUrza = menu.createAction(Ressources::whoTheFuckIsUrza(), 'w');
    menu.addMenuGroup({askAboutUrza}, {menu.createAction("Nothing")});
    if (menu.execute().key != 'w')
    {
        Console::printLn("\"No, not this time\", you think to yourself, and leave.");
    }
    Console::br();
    Console::printLn(std::format("You ask the question, that is lurkin around your head for so long now: {}?",
                                 Ressources::whoTheFuckIsUrza()));
    Console::printLn(
        std::format("The old man smiles, and replies: \"So, you want to know about {}?", Ressources::urza()));
    Console::printLn(
        "This is dangerous knowledge, nowadays. To get an answer to this question, you first have to become a hero!\"");
    Console::printLn("This was the most underwhelming answer you have ever heard in your live, since you asked the "
                     "beautiful farmers daughter to go for the dance when you was 8 years old.");
    Console::printLn("But your wanted to become a hero anyway, so you will have to come back later.");
    CGameManagement::getProgressionInstance()->reportModuleFinished(Ressources::Game::ShrineRessources::moduleName());
    _seenDuringPhase = CGameManagement::getProgressionInstance()->currentGameStage();
}

void CShrineOfTheAncients::stats() const
{
    Console::cls();
    Console::printLn("You take some time to think about yourself:");
    Console::br();

    auto progress = CGameManagement::getProgressionInstance()->getProgress();
    std::string progressString = "|";

    int i = 0;
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

    progressString.append("|");

    Console::printLnWithSpacer("Progress:", progressString);
    Console::printLnWithSpacer("BodyCount:",
                               std::format("{}", CGameManagement::getProgressionInstance()->getBodyCount()));
    Console::br();
    auto equipment = CGameManagement::getInventoryInstance()->getEquipment();
    for (auto e : equipment)
    {
        Console::printLnWithSpacer(e->typeName(), std::format("{} Level {}", e->name(), e->level()));
    }
    Console::confirmToContinue();
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
