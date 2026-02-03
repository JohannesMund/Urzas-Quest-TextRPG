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
#include "moduleinfo.h"

namespace ModuleRegister
{

void registerModules(CGameProgression* progression)
{
    /**
     * GamwStage: Start
     * Chapter 1
     */
    progression->registerModule(Shrine::moduleInfo());
    progression->registerModule(Bard::moduleInfo());

    /**
     * GameStage: SeenBard
     * Chapter 2
     */
    progression->registerModule(FishingVillageMakeRod::moduleInfo());
    progression->registerModule(RatFarm::moduleInfo());
    progression->registerModule(Sewer::moduleInfo());
    progression->registerModule(Leila::moduleInfo());

    /**
     * GameStage: ProvenAsHero
     * Chapter 3
     */
    progression->registerModule(FishingVillageMakeBoat::moduleInfo());
    progression->registerModule(LakeOfTears::moduleInfo());
    progression->registerModule(Cave::moduleInfo());
    progression->registerModule(SandwichShop::moduleInfo());

    /**
     * GameStage: LearnedAboutCult
     * Chapter 4
     */
    progression->registerModule(FishingVillageFishLegend::moduleInfo());
    progression->registerModule(RebellionHideout::moduleInfo());
    progression->registerModule(Leila2::moduleInfo());

    /**
     * GameStage: FoundCult
     * Chapter 5
     */
    progression->registerModule(BlackIvoryTower::moduleInfo());
    progression->registerModule(LeilaRescue::moduleInfo());
}
} // namespace ModuleRegister