#include "moduleressources.h"
#include "cdancingbard.h"
#include "cgamemanagement.h"
#include "colorconsole.h"

#include <format>
std::string BardRessources::moduleName()
{
    return "DancingBard";
}

std::string BardRessources::encounterName()
{
    return std::format("{}Dan{}cing {}Bard{}", CC::fgRed(), CC::fgLightRed(), CC::fgGreen(), CC::ccReset());
}

void BardRessources::initModule()
{
    CGameManagement::getInstance()->registerEncounter(new CDancingBard());
}

void BardRessources::deInitModule()
{
    CGameManagement::getInstance()->unregisterEncounterByModuleName(moduleName());
}
