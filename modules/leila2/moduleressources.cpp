#include "moduleressources.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "leila2/encounters/cleila2encounter.h"
#include "leila2/encounters/cleila2goblinencounter.h"
#include "ressources.h"

#include <format>

void Leila2Ressources::initModule()
{
    CGameManagement::getInstance()->registerEncounter(new CLeila2Encounter());
}

void Leila2Ressources::deInitModule()
{
    CGameManagement::getInstance()->unregisterEncounterByModuleName(encounterNameGuards());
    CGameManagement::getInstance()->unregisterEncounterByModuleName(encounterNameFindRibbon());
}

std::string Leila2Ressources::moduleName()
{
    return "RescuePrincessLaylaAgain";
}

std::string Leila2Ressources::encounterNameGuards()
{
    return "RescuePrincessLaylaAgainGuards";
}

std::string Leila2Ressources::encounterNameFindRibbon()
{

    return "RescuePrincessLaylaFindRibbon";
}

std::string Leila2Ressources::questLog()
{
    return std::format("Guard your favourite damsel in distress, {}, to the capital.",
                       Ressources::Game::princessLeila());
}

std::string Leila2Ressources::mork()
{
    return std::format("{}M{}ork{}", CC::fgGreen(), CC::fgLightGreen(), CC::ccReset());
}

std::string Leila2Ressources::gork()
{
    return std::format("{}G{}ork{}", CC::fgLightGreen(), CC::fgGreen(), CC::ccReset());
}

std::string Leila2Ressources::greenskin()
{
    return std::format("{}G{}reenskin{}", CC::fgGreen(), CC::fgLightGreen(), CC::ccReset());
}
