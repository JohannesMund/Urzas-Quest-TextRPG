#include "moduleressources.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "layla2/encounters/clayla2encounter.h"
#include "layla2/encounters/clayla2goblinencounter.h"
#include "ressources.h"

#include <format>

void Layla2Ressources::initModule()
{
    CGameManagement::getInstance()->registerEncounter(new CLayla2Encounter());
}

void Layla2Ressources::deInitModule()
{
    CGameManagement::getInstance()->unregisterEncounterByModuleName(encounterNameGuards());
    CGameManagement::getInstance()->unregisterEncounterByModuleName(encounterNameFindRibbon());
}

std::string Layla2Ressources::moduleName()
{
    return "RescuePrincessLaylaAgain";
}

std::string Layla2Ressources::encounterNameGuards()
{
    return "RescuePrincessLaylaAgainGuards";
}

std::string Layla2Ressources::encounterNameFindRibbon()
{

    return "RescuePrincessLaylaFindRibbon";
}

std::string Layla2Ressources::bimmel()
{
    return std::format("{0}Bi{1}mm{0}el{2}", CC::fgBlue(), CC::fgYellow(), CC::ccReset());
}

std::string Layla2Ressources::bommel()
{
    return std::format("{1}Bo{0}mm{1}el{2}", CC::fgBlue(), CC::fgYellow(), CC::ccReset());
}

std::string Layla2Ressources::questLog()
{
    return std::format("Guard your favourite damsel in distress, {}, to the capital.",
                       Ressources::Game::princessLayla());
}

std::string Layla2Ressources::mork()
{
    return std::format("{}M{}ork{}", CC::fgGreen(), CC::fgYellow(), CC::ccReset());
}

std::string Layla2Ressources::gork()
{
    return std::format("{}G{}ork{}", CC::fgYellow(), CC::fgGreen(), CC::ccReset());
}

std::string Layla2Ressources::ribbon()
{
    return std::format("{}R{}i{}bbon{}", CC::fgMagenta(), CC::fgWhite(), CC::fgLightMagenta(), CC::ccReset());
}

std::string Layla2Ressources::greenskin()
{
    return std::format("{}G{}reenskin{}", CC::fgGreen(), CC::fgLightGreen(), CC::ccReset());
}
