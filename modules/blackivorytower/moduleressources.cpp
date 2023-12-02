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
        moduleName(), std::format("Climb the {} and talk to {}.", darkIvoryTower(), Ressources::Game::mobi()));
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
    return std::format("{0}Dark {1}Ivory {0}Tower of the {2}Lu{3}na{4}ti{5}cs{6}",
                       CC::fgDarkGray(),
                       CC::fgLightGray(),
                       CC::fgYellow(),
                       CC::fgLightRed(),
                       CC::fgLightGreen(),
                       CC::fgLightCyan(),
                       CC::ccReset());

    return std::string();
}

std::string BlackIvoryTowerRessources::moduleName()
{
    return "BlackIvoryTowerofLunatics";
}
