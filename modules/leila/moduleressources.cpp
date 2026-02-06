#include "moduleressources.h"
#include "cgamemanagement.h"
#include "cleilaencounter.h"
#include "cleilatask.h"
#include "cleilatowntask.h"
#include "colorize.h"
#include "ctask.h"
#include "ressources.h"

#include <format>

Module::ModuleInfo Leila::moduleInfo()
{
    const auto taskFactory = [](const std::string_view& objectName) -> CTask*
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
    };

    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = moduleName();
    moduleInfo.translatorFile = "leila";
    moduleInfo.gameStage = Module::EGameStage::eSeenBard,

    moduleInfo.initFunction = []() { CGameManagement::getInstance()->registerEncounter(new CLeilaEncounter()); };
    moduleInfo.deInitFunction = []() { CGameManagement::getInstance()->unregisterEncounterByModuleName(moduleName()); };
    moduleInfo.questLogFunction = []()
    { return std::format("Rescue the beautiful {}.", Ressources::Game::princessLeila()); };

    moduleInfo.taskFactory = taskFactory;

    return moduleInfo;
}

std::string Leila::moduleName()
{
    return "RescuePrincessLayla";
}
