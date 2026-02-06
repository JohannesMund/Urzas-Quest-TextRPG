#include "moduleressources.h"
#include "cdancingbard.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "ressources.h"

#include <format>
std::string Bard::moduleName()
{
    return "DancingBard";
}

std::string Bard::encounterName()
{
    return Ressources::Game::dancingBard();
}

Module::ModuleInfo Bard::moduleInfo()
{
    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = moduleName();
    moduleInfo.translatorFile = "bard";
    moduleInfo.gameStage = Module::EGameStage::eStart,

    moduleInfo.initFunction = []() { CGameManagement::getInstance()->registerEncounter(new CDancingBard()); };
    moduleInfo.deInitFunction = []() { CGameManagement::getInstance()->unregisterEncounterByModuleName(moduleName()); };
    moduleInfo.questLogFunction = []()
    { return std::format("Watch a show of the {} when he performes in a town.", encounterName()); };

    return moduleInfo;
}