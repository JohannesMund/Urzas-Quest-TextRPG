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
#include "module/moduleinfo.h"
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
    progression->registerModule(ShrineInfo::moduleInfo());

    progression->registerModule(BardRessources::moduleName(),
                                Module::EGameStage::eStart,
                                &BardRessources::questLog,
                                &BardRessources::initModule,
                                &BardRessources::deInitModule);
    t->registerModule(BardRessources::moduleName(), "bard");

    /**
     * GameStage: SeenBard
     * Chapter 2
     */
    progression->registerModule(FishingVillageRessources::moduleNameMakeRod(),
                                Module::EGameStage::eSeenBard,
                                &FishingVillageRessources::questLogMakeRod,
                                &FishingVillageRessources::initModuleMakeRod,
                                &FishingVillageRessources::deInitModuleMakeRod,
                                &FishingVillageRessources::initWorldMap,
                                Module::noSupportCompanionFactory,
                                &FishingVillageRessources::roomFactory,
                                &FishingVillageRessources::itemFactory);
    t->registerModule(FishingVillageRessources::moduleNameMakeRod(), "fishingvillage");

    progression->registerModule(RatFarmRessources::moduleName(),
                                Module::EGameStage::eSeenBard,
                                &RatFarmRessources::questLog,
                                &RatFarmRessources::initModule,
                                &RatFarmRessources::deInitModule,
                                Module::noInitWorldMapFunction,
                                Module::noSupportCompanionFactory,
                                Module::noRoomFactory,
                                &RatFarmRessources::itemFactory,
                                &RatFarmRessources::taskFactory);
    t->registerModule(RatFarmRessources::moduleName(), "ratfarm");

    progression->registerModule(SewerRessources::moduleName(),
                                Module::EGameStage::eSeenBard,
                                &SewerRessources::questLog,
                                &SewerRessources::initModule,
                                &SewerRessources::deInitModule,
                                Module::noInitWorldMapFunction,
                                Module::noSupportCompanionFactory,
                                Module::noRoomFactory,
                                Module::noItemFactory,
                                &SewerRessources::taskFactory);
    t->registerModule(SewerRessources::moduleName(), "sewer");

    progression->registerModule(LeilaRessources::moduleName(),
                                Module::EGameStage::eSeenBard,
                                &LeilaRessources::questLog,
                                &LeilaRessources::initModule,
                                &LeilaRessources::deInitModule,
                                Module::noInitWorldMapFunction,
                                Module::noSupportCompanionFactory,
                                Module::noRoomFactory,
                                Module::noItemFactory,
                                &LeilaRessources::taskFactory);
    t->registerModule(LeilaRessources::moduleName(), "leila");

    /**
     * GameStage: ProvenAsHero
     * Chapter 3
     */
    progression->registerModule(FishingVillageRessources::moduleNameMakeBoat(),
                                Module::EGameStage::eProvenAsHero,
                                &FishingVillageRessources::questLogMAkeBoat,
                                &FishingVillageRessources::initModuleMakeBoat);
    t->registerModule(FishingVillageRessources::moduleNameMakeBoat(), "fishingvillage");

    progression->registerModule(LakeTearsRessources::moduleName(),
                                Module::EGameStage::eProvenAsHero,
                                &LakeTearsRessources::questLog,
                                &LakeTearsRessources::initModule,
                                &LakeTearsRessources::deInitModule,
                                Module::noInitWorldMapFunction,
                                Module::noSupportCompanionFactory,
                                Module::noRoomFactory,
                                Module::noItemFactory,
                                &LakeTearsRessources::taskFactory);
    t->registerModule(LakeTearsRessources::moduleName(), "lakeoftears");

    progression->registerModule(CaveRessources::moduleName(),
                                Module::EGameStage::eProvenAsHero,
                                &CaveRessources::questLog,
                                &CaveRessources::initModule,
                                &CaveRessources::deInitModule,
                                &CaveRessources::initWorldMap,
                                Module::noSupportCompanionFactory,
                                &CaveRessources::roomFactory,
                                Module::noItemFactory,
                                &CaveRessources::taskFactory);
    t->registerModule(CaveRessources::moduleName(), "cave");

    progression->registerModule(RebellionHideoutRessources::moduleNameSandwichShop(),
                                Module::EGameStage::eProvenAsHero,
                                &RebellionHideoutRessources::questLogSandwichShop,
                                &RebellionHideoutRessources::initModuleSandwichShop,
                                &RebellionHideoutRessources::deInitModuleSandwichShop,
                                &RebellionHideoutRessources::initWorldMap,
                                Module::noSupportCompanionFactory,
                                &RebellionHideoutRessources::roomFactory,
                                &RebellionHideoutRessources::itemFactory);
    t->registerModule(RebellionHideoutRessources::moduleNameSandwichShop(), "rebellionhideout");

    /**
     * GameStage: LearnedAboutCult
     * Chapter 4
     */
    progression->registerModule(FishingVillageRessources::moduleNameFishLegend(),
                                Module::EGameStage::eLearnedAboutCult,
                                &FishingVillageRessources::questLogFishLegend,
                                &FishingVillageRessources::initModuleFishLegend);
    t->registerModule(FishingVillageRessources::moduleNameFishLegend(), "fishingvillage");

    progression->registerModule(RebellionHideoutRessources::moduleNameRebellionHideout(),
                                Module::EGameStage::eLearnedAboutCult,
                                &RebellionHideoutRessources::questLogRebellionHideout,
                                &RebellionHideoutRessources::initModuleRebellionHideout,
                                &RebellionHideoutRessources::deInitModuleRebellionHideout);
    t->registerModule(RebellionHideoutRessources::moduleNameRebellionHideout(), "rebellionhideout");

    progression->registerModule(Leila2Ressources::moduleName(),
                                Module::EGameStage::eLearnedAboutCult,
                                &Leila2Ressources::questLog,
                                &Leila2Ressources::initModule,
                                &Leila2Ressources::deInitModule,
                                Module::noInitWorldMapFunction,
                                Module::noSupportCompanionFactory,
                                Module::noRoomFactory,
                                Module::noItemFactory,
                                &Leila2Ressources::taskFactory);
    t->registerModule(Leila2Ressources::moduleName(), "leila2");

    /**
     * GameStage: FoundCult
     * Chapter 5
     */
    progression->registerModule(BlackIvoryTowerRessources::moduleName(),
                                Module::EGameStage::eFoundCult,
                                &BlackIvoryTowerRessources::questLog,
                                &BlackIvoryTowerRessources::initModule,
                                &BlackIvoryTowerRessources::deInitModule,
                                &BlackIvoryTowerRessources::initWorldMap,
                                Module::noSupportCompanionFactory,
                                &BlackIvoryTowerRessources::roomFactory);
    t->registerModule(BlackIvoryTowerRessources::moduleName(), "blackivorytower");

    progression->registerModule(LeilaRescueRessources::moduleName(),
                                Module::EGameStage::eFoundCult,
                                &LeilaRescueRessources::questLog,
                                &LeilaRescueRessources::initModule,
                                &LeilaRescueRessources::deInitModule,
                                Module::noInitWorldMapFunction,
                                &LeilaRescueRessources::companionFactory,
                                Module::noRoomFactory,
                                &LeilaRescueRessources::itemFactory,
                                &LeilaRescueRessources::taskFactory);
    t->registerModule(LeilaRescueRessources::moduleName(), "leilarescue");
}
} // namespace ModuleRegister