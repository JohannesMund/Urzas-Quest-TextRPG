#include "cbattleinteraction.h"

#include "cbattle.h"
#include "cenemy.h"
#include "cmenu.h"
#include "cnpc.h"

CBattleInteraction::CBattleInteraction(CNpc* npc) : CNpcInteraction(npc, TagNames::NpcInteractions::battle)
{
}

bool CBattleInteraction::interactionAvailable() const
{
    return true;
}

void CBattleInteraction::executeInteraction()
{
    auto enemy = _npc->enemy();
    CBattle battle(enemy);
    battle.fight();
    delete enemy;
}

void CBattleInteraction::makeNav(CMenu& menu)
{
    _nav = menu.createAction({"Training battle", 'b'});
}
