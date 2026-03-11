#include "npcinteractions/cdateinteraction.h"
#include "cdateinteraction.h"
#include "cgamemanagement.h"
#include "cnpc.h"

CDateInteraction::CDateInteraction(CNpc* npc) : CNpcInteraction(npc, TagNames::NpcInteractions::date)
{
}
void CDateInteraction::executeInteraction()
{
    CNpcInteraction::executeInteraction();
    if (!_npc->isSignificantOther())
    {
        CGameManagement::getPlayerInstance()->setSignificantOther(_npc);
    }
}

bool CDateInteraction::interactionAvailable() const
{

    return CNpcInteraction::interactionAvailable() && _npc->isDatable();
}

void CDateInteraction::makeNav(CMenu& menu)
{
    _nav = menu.createAction({"Ask out", 'A'});
}
