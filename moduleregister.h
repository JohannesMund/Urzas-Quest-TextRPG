#pragma once

#include "ressources.h"

#include "modules/bard/moduleressources.h"
#include "modules/blackivorytower/moduleressources.h"
#include "modules/cave/moduleressources.h"
#include "modules/fishingvillage/moduleressources.h"
#include "modules/lakeoftears/moduleressources.h"
#include "modules/leila/moduleressources.h"
#include "modules/leila2/moduleressources.h"
#include "modules/leilarescue/moduleressources.h"
#include "modules/ratfarm/moduleressources.h"
#include "modules/rebellionhideout/moduleressources.h"
#include "modules/sewer/moduleressources.h"
#include "modules/shrineoftheancients/moduleressources.h"

#include "cgameprogression.h"
#include "translator/ctranslator.h"

namespace ModuleRegister
{

void registerModules(CGameProgression* progression)
{

    auto t = CTranslator::getInstance();

    /**
     * GamwStage: Start
     * Chapter 1
     */
    progression->registerModule(ShrineRessources::moduleName(),
                                CGameProgression::EGameStage::eStart,
                                &ShrineRessources::questLog,
                                &ShrineRessources::initModule,
                                &ShrineRessources::deInitModule,
                                &ShrineRessources::initWorldMap,
                                CGameProgression::noSupportCompanionFactory,
                                &ShrineRessources::roomFactory);
    t->registerModule(ShrineRessources::moduleName(), "shrineoftheancients");

    progression->registerModule(BardRessources::moduleName(),
                                CGameProgression::EGameStage::eStart,
                                &BardRessources::questLog,
                                &BardRessources::initModule,
                                &BardRessources::deInitModule);
    t->registerModule(BardRessources::moduleName(), "bard");

    /**
     * GameStage: SeenBard
     * Chapter 2
     */
    progression->registerModule(FishingVillageRessources::moduleNameMakeRod(),
                                CGameProgression::EGameStage::eSeenBard,
                                &FishingVillageRessources::questLogMakeRod,
                                &FishingVillageRessources::initModuleMakeRod,
                                &FishingVillageRessources::deInitModuleMakeRod,
                                &FishingVillageRessources::initWorldMap,
                                CGameProgression::noSupportCompanionFactory,
                                &FishingVillageRessources::roomFactory,
                                &FishingVillageRessources::itemFactory);
    t->registerModule(FishingVillageRessources::moduleNameMakeRod(), "fishingvillage");

    progression->registerModule(RatFarmRessources::moduleName(),
                                CGameProgression::EGameStage::eSeenBard,
                                &RatFarmRessources::questLog,
                                &RatFarmRessources::initModule,
                                &RatFarmRessources::deInitModule,
                                CGameProgression::noInitWorldMapFunction,
                                CGameProgression::noSupportCompanionFactory,
                                CGameProgression::noRoomFactory,
                                &RatFarmRessources::itemFactory,
                                &RatFarmRessources::taskFactory);
    t->registerModule(RatFarmRessources::moduleName(), "ratfarm");

    progression->registerModule(SewerRessources::moduleName(),
                                CGameProgression::EGameStage::eSeenBard,
                                &SewerRessources::questLog,
                                &SewerRessources::initModule,
                                &SewerRessources::deInitModule,
                                CGameProgression::noInitWorldMapFunction,
                                CGameProgression::noSupportCompanionFactory,
                                CGameProgression::noRoomFactory,
                                CGameProgression::noItemFactory,
                                &SewerRessources::taskFactory);
    t->registerModule(SewerRessources::moduleName(), "sewer");

    progression->registerModule(LeilaRessources::moduleName(),
                                CGameProgression::EGameStage::eSeenBard,
                                &LeilaRessources::questLog,
                                &LeilaRessources::initModule,
                                &LeilaRessources::deInitModule,
                                CGameProgression::noInitWorldMapFunction,
                                CGameProgression::noSupportCompanionFactory,
                                CGameProgression::noRoomFactory,
                                CGameProgression::noItemFactory,
                                &LeilaRessources::taskFactory);
    t->registerModule(LeilaRessources::moduleName(), "leila");

    /**
     * GameStage: ProvenAsHero
     * Chapter 3
     */
    progression->registerModule(FishingVillageRessources::moduleNameMakeBoat(),
                                CGameProgression::EGameStage::eProvenAsHero,
                                &FishingVillageRessources::questLogMAkeBoat,
                                &FishingVillageRessources::initModuleMakeBoat);
    t->registerModule(FishingVillageRessources::moduleNameMakeBoat(), "fishingvillage");

    progression->registerModule(LakeTearsRessources::moduleName(),
                                CGameProgression::EGameStage::eProvenAsHero,
                                &LakeTearsRessources::questLog,
                                &LakeTearsRessources::initModule,
                                &LakeTearsRessources::deInitModule,
                                CGameProgression::noInitWorldMapFunction,
                                CGameProgression::noSupportCompanionFactory,
                                CGameProgression::noRoomFactory,
                                CGameProgression::noItemFactory,
                                &LakeTearsRessources::taskFactory);
    t->registerModule(LakeTearsRessources::moduleName(), "lakeoftears");

    progression->registerModule(CaveRessources::moduleName(),
                                CGameProgression::EGameStage::eProvenAsHero,
                                &CaveRessources::questLog,
                                &CaveRessources::initModule,
                                &CaveRessources::deInitModule,
                                &CaveRessources::initWorldMap,
                                CGameProgression::noSupportCompanionFactory,
                                &CaveRessources::roomFactory,
                                CGameProgression::noItemFactory,
                                &CaveRessources::taskFactory);
    t->registerModule(CaveRessources::moduleName(), "cave");

    progression->registerModule(RebellionHideoutRessources::moduleNameSandwichShop(),
                                CGameProgression::EGameStage::eProvenAsHero,
                                &RebellionHideoutRessources::questLogSandwichShop,
                                &RebellionHideoutRessources::initModuleSandwichShop,
                                &RebellionHideoutRessources::deInitModuleSandwichShop,
                                &RebellionHideoutRessources::initWorldMap,
                                CGameProgression::noSupportCompanionFactory,
                                &RebellionHideoutRessources::roomFactory,
                                &RebellionHideoutRessources::itemFactory);
    t->registerModule(RebellionHideoutRessources::moduleNameSandwichShop(), "rebellionhideout");

    /**
     * GameStage: LearnedAboutCult
     * Chapter 4
     */
    progression->registerModule(FishingVillageRessources::moduleNameFishLegend(),
                                CGameProgression::EGameStage::eLearnedAboutCult,
                                &FishingVillageRessources::questLogFishLegend,
                                &FishingVillageRessources::initModuleFishLegend);
    t->registerModule(FishingVillageRessources::moduleNameFishLegend(), "fishingvillage");

    progression->registerModule(RebellionHideoutRessources::moduleNameRebellionHideout(),
                                CGameProgression::EGameStage::eLearnedAboutCult,
                                &RebellionHideoutRessources::questLogRebellionHideout,
                                &RebellionHideoutRessources::initModuleRebellionHideout,
                                &RebellionHideoutRessources::deInitModuleRebellionHideout);
    t->registerModule(RebellionHideoutRessources::moduleNameRebellionHideout(), "rebellionhideout");

    progression->registerModule(Leila2Ressources::moduleName(),
                                CGameProgression::EGameStage::eLearnedAboutCult,
                                &Leila2Ressources::questLog,
                                &Leila2Ressources::initModule,
                                &Leila2Ressources::deInitModule,
                                CGameProgression::noInitWorldMapFunction,
                                CGameProgression::noSupportCompanionFactory,
                                CGameProgression::noRoomFactory,
                                CGameProgression::noItemFactory,
                                &Leila2Ressources::taskFactory);
    t->registerModule(Leila2Ressources::moduleName(), "leila2");

    /**
     * GameStage: FoundCult
     * Chapter 5
     */
    progression->registerModule(BlackIvoryTowerRessources::moduleName(),
                                CGameProgression::EGameStage::eFoundCult,
                                &BlackIvoryTowerRessources::questLog,
                                &BlackIvoryTowerRessources::initModule,
                                &BlackIvoryTowerRessources::deInitModule,
                                &BlackIvoryTowerRessources::initWorldMap,
                                CGameProgression::noSupportCompanionFactory,
                                &BlackIvoryTowerRessources::roomFactory);
    t->registerModule(BlackIvoryTowerRessources::moduleName(), "blackivorytower");

    progression->registerModule(LeilaRescueRessources::moduleName(),
                                CGameProgression::EGameStage::eFoundCult,
                                &LeilaRescueRessources::questLog,
                                &LeilaRescueRessources::initModule,
                                &LeilaRescueRessources::deInitModule,
                                CGameProgression::noInitWorldMapFunction,
                                &LeilaRescueRessources::companionFactory,
                                CGameProgression::noRoomFactory,
                                &LeilaRescueRessources::itemFactory,
                                &LeilaRescueRessources::taskFactory);
    t->registerModule(LeilaRescueRessources::moduleName(), "leilarescue");
}
} // namespace ModuleRegister