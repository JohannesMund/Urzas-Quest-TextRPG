#pragma once

#include "bard/cdancingbard.h"
#include "cave/ccavebattleencounter.h"
#include "ratfarm/cratfarmencounter.h"

#include "cbattleencounter.h"
#include "cdeadhero.h"
#include "cgamemanagement.h"
#include "cmysteriouschest.h"

namespace EncounterRegister
{
void encounterRegister()
{
    CGameManagement::getInstance()->registerEncounter(new CMysteriousChest());
    CGameManagement::getInstance()->registerEncounter(new CDeadHero());
    CGameManagement::getInstance()->registerEncounter(new CBattleEncounter());
    CGameManagement::getInstance()->registerEncounter(new CDancingBard());
    CGameManagement::getInstance()->registerEncounter(new CCaveBattleEncounter());
    CGameManagement::getInstance()->registerEncounter(new CRatFarmEncounter());
}
} // namespace EncounterRegister
