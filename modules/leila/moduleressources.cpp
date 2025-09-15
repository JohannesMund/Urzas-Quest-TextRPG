#include "moduleressources.h"
#include "cgamemanagement.h"
#include "cleilaencounter.h"
#include "cleilatask.h"
#include "cleilatowntask.h"
#include "colorize.h"
#include "ctask.h"
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

CTask* LeilaRessources::taskFactory(const std::string_view& objectName)
{
    if (TagNames::Leila::leila.compare(objectName) == 0)
    {
        return new CLeilaTask();
    }
    if (TagNames::Leila::leilaTown.compare(objectName) == 0)
    {
        return new CLeilaTownTask();
    }
    return nullptr;
}

std::string LeilaRessources::moduleName()
{
    return "RescuePrincessLayla";
}

std::string LeilaRessources::questLog()
{
    return std::format("Rescue the beautiful {}.", Ressources::Game::princessLeila());
}
