#include "moduleressources.h"
#include "cgamemanagement.h"
#include "claylaencounter.h"
#include "colorize.h"
#include "ressources.h"

#include <format>

void LaylaRessources::initModule()
{
    CGameManagement::getInstance()->registerEncounter(new CLaylaEncounter());
}

void LaylaRessources::deInitModule()
{
    CGameManagement::getInstance()->unregisterEncounterByModuleName(LaylaRessources::moduleName());
}

std::string LaylaRessources::moduleName()
{
    return "RescuePrincessLayla";
}

std::string LaylaRessources::piefke()
{
    return std::format("{0}Pi{1}ef{0}ke{2}", CC::fgBlue(), CC::fgYellow(), CC::ccReset());
}

std::string LaylaRessources::schniefke()
{
    return std::format("{1}Sch{0}nie{1}fke{2}", CC::fgBlue(), CC::fgYellow(), CC::ccReset());
}

std::string LaylaRessources::questLog()
{
    return std::format("Rescue the beautiful {}", Ressources::Game::princessLayla());
}
