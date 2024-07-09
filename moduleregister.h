#pragma once

#include "ressources.h"

#include "modules/bard/moduleressources.h"
#include "modules/blackivorytower/moduleressources.h"
#include "modules/cave/moduleressources.h"
#include "modules/fishingvillage/moduleressources.h"
#include "modules/lakeoftears/moduleressources.h"
#include "modules/leila/moduleressources.h"
#include "modules/leila2/moduleressources.h"
#include "modules/ratfarm/moduleressources.h"
#include "modules/rebellionhideout/moduleressources.h"
#include "modules/sewer/moduleressources.h"
#include "modules/shrineoftheancients/moduleressources.h"

#include "cgameprogression.h"

namespace ModuleRegister
{
void registerModules(CGameProgression* progression)
{

    progression->registerModule(ShrineRessources::moduleName(),
                                CGameProgression::EGameStage::eStart,
                                &ShrineRessources::questLog,
                                &ShrineRessources::initModule,
                                &ShrineRessources::deInitModule,
                                &ShrineRessources::initWorldMap);

    progression->registerModule(BardRessources::moduleName(),
                                CGameProgression::EGameStage::eStart,
                                &BardRessources::questLog,
                                &BardRessources::initModule,
                                &BardRessources::deInitModule);

    progression->registerModule(FishingVillageRessources::moduleNameMakeRod(),
                                CGameProgression::EGameStage::eSeenBard,
                                &FishingVillageRessources::questLogMakeRod,
                                &FishingVillageRessources::initModuleMakeRod,
                                &FishingVillageRessources::deInitModuleMakeRod,
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

    progression->registerModule(LeilaRessources::moduleName(),
                                CGameProgression::EGameStage::eSeenBard,
                                &LeilaRessources::questLog,
                                &LeilaRessources::initModule,
                                &LeilaRessources::deInitModule);

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
    progression->registerModule(Leila2Ressources::moduleName(),
                                CGameProgression::EGameStage::eLearnedAboutCult,
                                &Leila2Ressources::questLog,
                                &Leila2Ressources::initModule,
                                &Leila2Ressources::deInitModule);

    progression->registerModule(BlackIvoryTowerRessources::moduleName(),
                                CGameProgression::EGameStage::eFoundCult,
                                &BlackIvoryTowerRessources::questLog,
                                &BlackIvoryTowerRessources::initModule,
                                &BlackIvoryTowerRessources::deInitModule,
                                &BlackIvoryTowerRessources::initWorldMap);
}
} // namespace ModuleRegister