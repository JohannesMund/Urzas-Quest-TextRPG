#include "moduleressources.h"
#include "cgamemanagement.h"
#include "claylaencounter.h"
#include "colorconsole.h"

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

std::string LaylaRessources::layla()
{

    return std::format("{1}Princess {0}L{1}ayla{2}", CC::fgLightMagenta(), CC::fgBlue(), CC::ccReset());
}
