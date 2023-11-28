#include "moduleressources.h"
#include "cgamemanagement.h"
#include "clakeoftearsencounter.h"
#include "colorize.h"
#include "ressources.h"

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

std::string LakeTearsRessources::questLog()
{
    return "Find and remove the source of the salty water.";
}

std::string LakeTearsRessources::getColoredsBossString()
{
    return std::format("{} and {}", Ressources::Game::bimmelchen(), Ressources::Game::pimmelchen());
}
