#include "clayla2capitaltask.h"
#include "cgamemanagement.h"
#include "citemfactory.h"
#include "colorize.h"
#include "console.h"
#include "ctown.h"
#include "layla2/moduleressources.h"
#include "ressources.h"
#include <format>

CLayla2CapitalTask::CLayla2CapitalTask()
{
}

void CLayla2CapitalTask::execute()
{
    std::string townName;
    auto town = dynamic_cast<CTown*>(CGameManagement::getInstance()->currentRoom());
    if (town != nullptr)
    {
        townName = town->name();
    }

    Console::printLn(
        std::format("Finally, you arrive at {}. You kept your promise and brought {} back home. This time you are let "
                    "in and the guard leads you to the thrown room, where {} is happy to see his daughter again.",
                    townName,
                    Ressources::Game::princessLayla(),
                    Ressources::Game::kingJesster()));
    Console::printLn(
        std::format("Taking a closer look at the king, you realize, that he is not the sublime type of wise, old man, "
                    "you would expect from a king. he looks... funny. He is dressed like a jester, and he looks like "
                    "a jester. You never questioned his name, but now, as you see him tha name {} makes sense to you. "
                    "You wonder if the people of the land know, that they are ruled by a mere clown?",
                    Ressources::Game::kingJesster()));
    Console::printLn(std::format(
        "{} immediately starts complaining about the long hard walk, and her hurting feet, nothing you have not heard "
        "the whole time. {} hugs his daughter and smiles at you. \"I suppose i have to thank you.\"",
        Ressources::Game::layla(),
        Ressources::Game::kingJesster()));
    Console::printLn("This whole \"nameless hero\" - thing is going to far, you need a name! But before you can start "
                     "thinking about one, the king continues:");
    Console::br();
    auto item = CGameManagement::getItemFactoryInstance()->makeEquipment(Ressources::Items::EType::eWeapon,
                                                                         Ressources::Items::EQuality::eAwesomne);

    Console::printLn(
        std::format("\"As a sign of thankfulness, for saving my daughter, i hand you the {}, an old heirloom of the "
                    "royal family. This should make things more than even. Above this, i must ask you to leave, "
                    "because people like you, and especially you, are not welcomned here.\"",
                    item->name()));
    Console::confirmToContinue();
    Console::br();
    CGameManagement::getInventoryInstance()->addItem(item);
    Console::printLn("This said, the guards lead you out of the capital, without even giving you a chance to say "
                     "goodby to the princess. What an underwhelming adventuere!");
    Console::printLn("You start thinking about abducting the princess yourself.");
    Console::br();
    Console::confirmToContinue();
    CGameManagement::getProgressionInstance()->reportModuleFinished(Layla2Ressources::moduleName());
    _isFinished = true;
}
