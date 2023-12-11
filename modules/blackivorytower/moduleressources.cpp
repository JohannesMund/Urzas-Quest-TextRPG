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
