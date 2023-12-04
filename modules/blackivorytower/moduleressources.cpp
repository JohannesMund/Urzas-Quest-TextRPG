#include "moduleressources.h"
#include "cblackivorytower.h"
#include "cgamemanagement.h"
#include "cgameprogression.h"
#include "colorize.h"
#include "croom.h"
#include "ressources.h"

#include <format>

void BlackIvoryTowerRessources::initModule()
{
    CGameManagement::getProgressionInstance()->registerModuleQuest(
        moduleName(),
        std::format("{1} is a former Member of the Rebellion. She left the rebellion for good, but is still an ally to "
                    "the rebellion. She lives on top of the {0}, a gigantic tower, guarded by {1}s {2}. Climb the "
                    "{0} and talk to {1}.{3}",
                    darkIvoryTower(),
                    Ressources::Game::mobi(),
                    lunatics(),
                    CC::ccReset()));
}
void BlackIvoryTowerRessources::deInitModule()
{
}
void BlackIvoryTowerRessources::initWorldMap(std::vector<CRoom*>& rooms)
{
    rooms.push_back(new CBlackIvoryTower());
}

std::string BlackIvoryTowerRessources::questLog()
{
    return std::format("Climb up the {}", darkIvoryTower());
}

std::string BlackIvoryTowerRessources::darkIvoryTower()
{
    return std::format("{0}Dark {1}Ivory {0}Tower of the {2}", CC::fgDarkGray(), CC::fgLightGray(), lunatics());

    return std::string();
}

std::string BlackIvoryTowerRessources::lunatic()
{
    return std::format(
        "{}Lu{}na{}ti{}c{}", CC::fgYellow(), CC::fgLightRed(), CC::fgLightGreen(), CC::fgLightCyan(), CC::ccReset());
}

std::string BlackIvoryTowerRessources::lunatics()
{
    return std::format("{}{}s{}", lunatic(), CC::fgLightCyan(), CC::ccReset());
}

std::string BlackIvoryTowerRessources::moduleName()
{
    return "BlackIvoryTowerofLunatics";
}
