#include "moduleressources.h"
#include "cgamemanagement.h"
#include "clakeoftearsencounter.h"
#include "colorconsole.h"

#include <format>
#include <string>

std::string LakeTearsRessources::moduleName()
{
    return "LakeOfTears";
}

void LakeTearsRessources::initModule()
{
    CGameManagement::getInstance()->registerEncounter(new CLakeOfTearsEncounter());
}

void LakeTearsRessources::deInitModule()
{
    CGameManagement::getInstance()->unregisterEncounterByModuleName(moduleName());
}

std::string LakeTearsRessources::getColoredBossString()
{
    return std::format("{} and {}", bimmelchen(), pimmelchen());
}

std::string LakeTearsRessources::bimmelchen()
{
    return std::format("{0}B{1}immelchen{2}", CC::fgLightBlue(), CC::fgLightMagenta(), CC::ccReset());
}

std::string LakeTearsRessources::pimmelchen()
{
    return std::format("{1}P{0}immelchen{2}", CC::fgLightBlue(), CC::fgLightMagenta(), CC::ccReset());
}
