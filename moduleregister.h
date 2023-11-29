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

#include "cgameprogression.h"

#include <functional>
#include <string>
#include <vector>

class ModuleRegister
{
public:
    static void registerModules(CGameProgression* progression)
    {

        progression->registerModule(Ressources::Game::ShrineRessources::moduleName(),
                                    CGameProgression::EGameStage::eStart);

        progression->registerModule(BardRessources::moduleName(),
                                    CGameProgression::EGameStage::eStart,
                                    &BardRessources::questLog,
                                    &BardRessources::initModule,
                                    &BardRessources::deInitModule);

        progression->registerModule(FishingVillageRessources::moduleNameMakeRod(),
                                    CGameProgression::EGameStage::eSeenBard,
                                    &FishingVillageRessources::questLogMakeRod,
                                    &FishingVillageRessources::initModuleMakeRod,
                                    &CGameProgression::Module::noInitDeInitFunction,
                                    &FishingVillageRessources::initWorldMap);
        progression->registerModule(RatFarmRessources::moduleName(),
                                    CGameProgression::EGameStage::eSeenBard,
                                    &RatFarmRessources::questLog,
                                    &RatFarmRessources::initModule,
                                    &RatFarmRessources::deInitModule);

        progression->registerModule(SewerRessources::moduleName(),
                                    CGameProgression::EGameStage::eSeenBard,
                                    &SewerRessources::questLog,
                                    &SewerRessources::initModule,
                                    &SewerRessources::deInitModule);

        progression->registerModule(LaylaRessources::moduleName(),
                                    CGameProgression::EGameStage::eSeenBard,
                                    &LaylaRessources::questLog,
                                    &LaylaRessources::initModule,
                                    &LaylaRessources::deInitModule);

        progression->registerModule(FishingVillageRessources::moduleNameMakeBoat(),
                                    CGameProgression::EGameStage::eProvenAsHero,
                                    &FishingVillageRessources::questLogMAkeBoat,
                                    &FishingVillageRessources::initModuleMakeBoat);
        progression->registerModule(LakeTearsRessources::moduleName(),
                                    CGameProgression::EGameStage::eProvenAsHero,
                                    &LakeTearsRessources::questLog,
                                    &LakeTearsRessources::initModule,
                                    &LakeTearsRessources::deInitModule);
        progression->registerModule(CaveRessources::moduleName(),
                                    CGameProgression::EGameStage::eProvenAsHero,
                                    &CaveRessources::questLog,
                                    &CaveRessources::initModule,
                                    &CaveRessources::deInitModule,
                                    &CaveRessources::initWorldMap);
        progression->registerModule(RebellionHideoutRessources::moduleNameSandwichShop(),
                                    CGameProgression::EGameStage::eProvenAsHero,
                                    &RebellionHideoutRessources::questLogSandwichShop,
                                    &RebellionHideoutRessources::initModuleSandwichShop,
                                    &RebellionHideoutRessources::deInitModuleSandwichShop,
                                    &RebellionHideoutRessources::initWorldMap);

        progression->registerModule(FishingVillageRessources::moduleNameFishLegend(),
                                    CGameProgression::EGameStage::eLearnedAboutCult,
                                    &FishingVillageRessources::questLogFishLegend,
                                    &FishingVillageRessources::initModuleFishLegend);
        progression->registerModule(RebellionHideoutRessources::moduleNameRebellionHideout(),
                                    CGameProgression::EGameStage::eLearnedAboutCult,
                                    &RebellionHideoutRessources::questLogRebellionHideout,
                                    &RebellionHideoutRessources::initModuleRebellionHideout,
                                    &RebellionHideoutRessources::deInitModuleRebellionHideout);
        progression->registerModule(Layla2Ressources::moduleName(),
                                    CGameProgression::EGameStage::eLearnedAboutCult,
                                    &Layla2Ressources::questLog,
                                    &Layla2Ressources::initModule,
                                    &Layla2Ressources::deInitModule);
    }
};