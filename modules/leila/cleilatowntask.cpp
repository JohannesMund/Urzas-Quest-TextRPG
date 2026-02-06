#include "cleilatowntask.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "ctown.h"
#include "moduleressources.h"
#include "ressources.h"

#include <format>

CLeilaTownTask::CLeilaTownTask() : CTask(TagNames::Leila::leilaTown)
{
    _isAutoExecute = false;
}

void CLeilaTownTask::execute()
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

    Console::printLn(
        "Your search ends in a very dark and very shady corner of the town, where you wake up in "
        "the gutter with a terrible headache and not the slightest idea, what braught you there. Your Money is "
        "gone. But you have a new tatoo. It reads:");
    Console::printLn(std::format("{} {}is geila{}", Ressources::Game::leila(), CC::fgLightMagenta(), CC::ccReset()),
                     Console::EAlignment::eCenter);
    Console::printLn("Whatever that means.");
    Console::br();

    CGameManagement::getPlayerInstance()->loseGold(CGameManagement::getPlayerInstance()->gold());
    CGameManagement::getProgressionInstance()->reportModuleFinished(Leila::moduleName());
    _isFinished = true;
}

std::string CLeilaTownTask::taskNav() const
{
    return std::format("Ask about {} and {}", Ressources::Game::fiego(), Ressources::Game::brock());
}
