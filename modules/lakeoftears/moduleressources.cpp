#include "moduleressources.h"
#include "cgamemanagement.h"
#include "clakeoftearsbosstask.h"
#include "clakeoftearsencounter.h"
#include "clakeoftearstask.h"
#include "colorize.h"
#include "ctask.h"
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

CTask* LakeTearsRessources::taskFactory(const std::string_view& objectName)
{
    if (TagNames::LakeOfTears::lakeOfTears.compare(objectName) == 0)
    {
        return new CLakeOfTearsTask();
    }
    if (TagNames::LakeOfTears::lakeOfTearsBoss.compare(objectName) == 0)
    {
        return new CLakeOfTearsBossTask();
    }
    return nullptr;
}

std::string LakeTearsRessources::questLog()
{
    return "Find and remove the source of the salty water.";
}

std::string LakeTearsRessources::getColoredsBossString()
{
    return std::format("{} and {}", Ressources::Game::bimmelchen(), Ressources::Game::pimmelchen());
}
