#include "ctalkinteraction.h"

#include "cgamestateobject.h"
#include "cmenu.h"

CTalkInteraction::CTalkInteraction(CNpc* npc, const std::string_view& objectName) : CNpcInteraction(npc, objectName)
{
}

bool CTalkInteraction::interactionAvailable() const
{
    return true;
}

void CTalkInteraction::makeNav(CMenu& menu)
{
    _nav = menu.createAction({"Talk", 'T'});
}
