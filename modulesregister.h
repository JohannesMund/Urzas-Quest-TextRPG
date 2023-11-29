#pragma once

#include "ressources.h"

#include "modules/bard/moduleressources.h"
#include "modules/cave/moduleressources.h"
#include "modules/fishingvillage/moduleressources.h"
#include "modules/lakeoftears/moduleressources.h"
#include "modules/layla/moduleressources.h"
#include "modules/layla2/moduleressources.h"
#include "modules/ratfarm/moduleressources.h"
#include "modules/rebellionhideout/moduleressources.h"
#include "modules/sewer/moduleressources.h"

#include <functional>
#include <string>
#include <vector>

class CRoom;

namespace ModuleRegister
{

struct Module
{
    std::string moduleName;
    Ressources::Game::EGameStage gameStage;
    std::function<std::string()> questLogFunction;
    std::function<void()> initFunction;
    std::function<void()> deInitFunction;
    std::function<void(std::vector<CRoom*>&)> initWorldMapFunction;

    static std::function<bool(const Module)> moduleRegisterNameFilter(const std::string_view& name)
    {
        return [name](const auto module) { return module.moduleName.compare(name) == 0; };
    }
    static std::function<bool(const Module)> moduleRegisterStageFilter(const Ressources::Game::EGameStage& stage)
    {
        return [stage](auto module) { return module.gameStage == stage; };
    }

    static void noInitDeInitFunction()
    {
    }
    static void noInitWorldMapFunction(std::vector<CRoom*>&)
    {
    }
    static std::string noQuestLogFunction()
    {
        return std::string{};
    }
};

Module makeModule(const std::string_view& name,
                  const Ressources::Game::EGameStage neededForStage,
                  std::function<std::string()> questLogFunction = &Module::noQuestLogFunction,
                  std::function<void()> initFunction = &Module::noInitDeInitFunction,
                  std::function<void()> deInitFunction = &Module::noInitDeInitFunction,
                  std::function<void(std::vector<CRoom*>&)> initWorldMapFunction = &Module::noInitWorldMapFunction)
{
    ModuleRegister::Module module;
    module.moduleName = name;
    module.gameStage = neededForStage;
    module.questLogFunction = questLogFunction;
    module.initFunction = initFunction;
    module.deInitFunction = deInitFunction;
    module.initWorldMapFunction = initWorldMapFunction;
    return module;
}

std::vector<Module> registerModules()
{
    std::vector<Module> modules;

    modules.push_back(
        makeModule(Ressources::Game::ShrineRessources::moduleName(), Ressources::Game::EGameStage::eStart));

    modules.push_back(makeModule(BardRessources::moduleName(),
                                 Ressources::Game::EGameStage::eStart,
                                 &BardRessources::questLog,
                                 &BardRessources::initModule,
                                 &BardRessources::deInitModule));

    modules.push_back(makeModule(FishingVillageRessources::moduleNameMakeRod(),
                                 Ressources::Game::EGameStage::eSeenBard,
                                 &FishingVillageRessources::questLogMakeRod,
                                 &FishingVillageRessources::initModuleMakeRod,
                                 &ModuleRegister::Module::noInitDeInitFunction,
                                 &FishingVillageRessources::initWorldMap));
    modules.push_back(makeModule(RatFarmRessources::moduleName(),
                                 Ressources::Game::EGameStage::eSeenBard,
                                 &RatFarmRessources::questLog,
                                 &RatFarmRessources::initModule,
                                 &RatFarmRessources::deInitModule));

    modules.push_back(makeModule(SewerRessources::moduleName(),
                                 Ressources::Game::EGameStage::eSeenBard,
                                 &SewerRessources::questLog,
                                 &SewerRessources::initModule,
                                 &SewerRessources::deInitModule));

    modules.push_back(makeModule(LaylaRessources::moduleName(),
                                 Ressources::Game::EGameStage::eSeenBard,
                                 &LaylaRessources::questLog,
                                 &LaylaRessources::initModule,
                                 &LaylaRessources::deInitModule));

    modules.push_back(makeModule(FishingVillageRessources::moduleNameMakeBoat(),
                                 Ressources::Game::EGameStage::eProvenAsHero,
                                 &FishingVillageRessources::questLogMAkeBoat,
                                 &FishingVillageRessources::initModuleMakeBoat));
    modules.push_back(makeModule(LakeTearsRessources::moduleName(),
                                 Ressources::Game::EGameStage::eProvenAsHero,
                                 &LakeTearsRessources::questLog,
                                 &LakeTearsRessources::initModule,
                                 &LakeTearsRessources::deInitModule));
    modules.push_back(makeModule(CaveRessources::moduleName(),
                                 Ressources::Game::EGameStage::eProvenAsHero,
                                 &CaveRessources::questLog,
                                 &CaveRessources::initModule,
                                 &CaveRessources::deInitModule,
                                 &CaveRessources::initWorldMap));
    modules.push_back(makeModule(RebellionHideoutRessources::moduleNameSandwichShop(),
                                 Ressources::Game::EGameStage::eProvenAsHero,
                                 &RebellionHideoutRessources::questLogSandwichShop,
                                 &RebellionHideoutRessources::initModuleSandwichShop,
                                 &RebellionHideoutRessources::deInitModuleSandwichShop,
                                 &RebellionHideoutRessources::initWorldMap));

    modules.push_back(makeModule(FishingVillageRessources::moduleNameFishLegend(),
                                 Ressources::Game::EGameStage::eLearnedAboutCult,
                                 &FishingVillageRessources::questLogFishLegend,
                                 &FishingVillageRessources::initModuleFishLegend));
    modules.push_back(makeModule(RebellionHideoutRessources::moduleNameRebellionHideout(),
                                 Ressources::Game::EGameStage::eLearnedAboutCult,
                                 &RebellionHideoutRessources::questLogRebellionHideout,
                                 &RebellionHideoutRessources::initModuleRebellionHideout,
                                 &RebellionHideoutRessources::deInitModuleRebellionHideout));
    modules.push_back(makeModule(Layla2Ressources::moduleName(),
                                 Ressources::Game::EGameStage::eLearnedAboutCult,
                                 &Layla2Ressources::questLog,
                                 &Layla2Ressources::initModule,
                                 &Layla2Ressources::deInitModule));
    return modules;
}

} // namespace ModuleRegister