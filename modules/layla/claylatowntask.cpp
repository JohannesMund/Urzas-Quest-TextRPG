#include "claylatowntask.h"
#include "cgamemanagement.h"
#include "colorconsole.h"
#include "console.h"
#include "ctown.h"
#include "moduleressources.h"
#include "ressources.h"

#include <format>

CLaylaTownTask::CLaylaTownTask()
{
    _isAutoExecute = false;
}

void CLaylaTownTask::execute()
{
    std::string townName;
    auto town = dynamic_cast<CTown*>(CGameManagement::getInstance()->currentRoom());
    if (town != nullptr)
    {
        townName = town->name();
    }

    Console::printLn(std::format("{} is a good place for gathering information. You ask around for information about "
                                 "{} and {} and people are more willing to answer you.",
                                 townName,
                                 Ressources::Game::fiego(),
                                 Ressources::Game::brock()));
    Console::printLn("Both are not regarded as evil villains, more like leader of the resistance. Probably people dont "
                     "know, that they kidnap innocent princesses.");
    Console::printLn(std::format("You hear the name {0} here and there, but usually the talk ends at that point. At "
                                 "least you learn, that {1} and {2} are pro-{0}.",
                                 Ressources::Game::urza(),
                                 Ressources::Game::fiego(),
                                 Ressources::Game::brock()));
    Console::printLn("Your search ends in a very dark and shady corner of the town, where you wake up in "
                     "the gutter with a terrible headache and not the slightest idea, how you came here. Your Money is "
                     "gone. But you have a new tatoo. It reads:");
    Console::printLn(std::format("{} {}is geila{}", Ressources::Game::layla(), CC::fgLightMagenta(), CC::ccReset()),
                     Console::EAlignment::eCenter);
    Console::printLn("Whatever that means.");

    CGameManagement::getPlayerInstance()->addGold(CGameManagement::getPlayerInstance()->gold() * -1);
    CGameManagement::getProgressionInstance()->reportModuleFinished(LaylaRessources::moduleName());
    _isFinished = true;
}

std::string CLaylaTownTask::taskNav() const
{
    return std::format("Ask about {} and {}", Ressources::Game::fiego(), Ressources::Game::brock());
}
