#include "moduleressources.h"
#include "cgamemanagement.h"
#include "cleilaencounter.h"
#include "colorize.h"
#include "ressources.h"

#include <format>

void LeilaRessources::initModule()
{
    CGameManagement::getInstance()->registerEncounter(new CLeilaEncounter());
}

void LeilaRessources::deInitModule()
{
    CGameManagement::getInstance()->unregisterEncounterByModuleName(LeilaRessources::moduleName());
}

std::string LeilaRessources::moduleName()
{
    return "RescuePrincessLayla";
}

std::string LeilaRessources::questLog()
{
    return std::format("Rescue the beautiful {}.", Ressources::Game::princessLeila());
}
