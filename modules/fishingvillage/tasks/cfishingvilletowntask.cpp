#include "cfishingvilletowntask.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "ctown.h"
#include "fishingvillage/moduleressources.h"
#include "ressources.h"

#include <format>

CFishingVilleTownTask::CFishingVilleTownTask() : CTask(TagNames::FishingVille::fishingVilleTask)
{
    _isAutoExecute = true;
}

void CFishingVilleTownTask::execute()
{
    _isFinished = true;

    std::string townName;
    auto town = dynamic_cast<CTown*>(CGameManagement::getInstance()->currentRoom());
    if (town != nullptr)
    {
        townName = town->name();
    }

    Console::printLn(std::format(
        "{}, {} and {}, those are the names, you must find out more about. Here in {} you need to find answers!",
        Ressources::Game::urza(),
        Ressources::Game::fiego(),
        Ressources::Game::brock(),
        townName));
    Console::printLn(
        std::format("The last time, you tried to find those information, you ended up in the gutter, with no money, "
                    "and a tatoo of {} on your arm. At least something, but definitely not what you where looking for.",
                    Ressources::Game::princessLeila()));
    Console::printLn(
        std::format("This time, you consciously avoid the dark and shady areas of {}, and ask around. still nobody "
                    "wants to talk about {}, {} and {}, but at least you get one hint: Appearently, {} is one of the "
                    "\"Know it alls\" in this world. You know this guy very well by now. you sold him so many fishes. "
                    "Maybe, you should pay him another visit, and try to find out what you are looking for.",
                    townName,
                    Ressources::Game::urza(),
                    Ressources::Game::fiego(),
                    Ressources::Game::brock(),
                    Ressources::Game::fishingFritz()));
    Console::confirmToContinue();
}
