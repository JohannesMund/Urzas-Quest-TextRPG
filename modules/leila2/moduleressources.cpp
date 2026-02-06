#include "moduleressources.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "ctask.h"
#include "leila2/encounters/cleila2encounter.h"
#include "leila2/encounters/cleila2goblinencounter.h"
#include "leila2/tasks/cleila2capitaltask.h"
#include "leila2/tasks/cleila2goblinvillagetask.h"
#include "ressources.h"

#include <format>

std::string Leila2::moduleName()
{
    return "RescuePrincessLaylaAgain";
}

Module::ModuleInfo Leila2::moduleInfo()
{

    const auto taskFactory = [](const std::string_view& objectName) -> CTask*
    {
        if (TagNames::Leila2::leilaCaptial.compare(objectName) == 0)
        {
            return new CLeila2CapitalTask();
        }
        if (TagNames::Leila2::goblinVillage.compare(objectName) == 0)
        {
            return new CLeila2GoblinVillageTask();
        }
        return nullptr;
    };

    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = moduleName();
    moduleInfo.translatorFile = "leila2";
    moduleInfo.gameStage = Module::EGameStage::eLearnedAboutCult,

    moduleInfo.initFunction = []() { CGameManagement::getInstance()->registerEncounter(new CLeila2Encounter()); };
    moduleInfo.deInitFunction = []()
    {
        CGameManagement::getInstance()->unregisterEncounterByModuleName(encounterNameGuards());
        CGameManagement::getInstance()->unregisterEncounterByModuleName(encounterNameFindRibbon());
    };
    moduleInfo.questLogFunction = []()
    {
        return std::format("Guard your favourite damsel in distress, {}, to the capital.",
                           Ressources::Game::princessLeila());
    };
    moduleInfo.taskFactory = taskFactory;

    return moduleInfo;
}

std::string Leila2::encounterNameGuards()
{
    return "RescuePrincessLaylaAgainGuards";
}

std::string Leila2::encounterNameFindRibbon()
{

    return "RescuePrincessLaylaFindRibbon";
}

std::string Leila2::mork()
{
    return std::format("{}M{}ork{}", CC::fgGreen(), CC::fgLightGreen(), CC::ccReset());
}

std::string Leila2::gork()
{
    return std::format("{}G{}ork{}", CC::fgLightGreen(), CC::fgGreen(), CC::ccReset());
}

std::string Leila2::greenskin()
{
    return std::format("{}G{}reenskin{}", CC::fgGreen(), CC::fgLightGreen(), CC::ccReset());
}
