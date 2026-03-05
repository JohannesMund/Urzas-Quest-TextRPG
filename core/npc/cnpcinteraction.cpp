#include "cnpcinteraction.h"

#include "cmenu.h"
#include "cnpc.h"

#include <nlohmann/json.hpp>

CNpcInteraction::CNpcInteraction(CNpc* npc) : CGameStateObject(TagNames::Translator::npcInteraction), _npc(npc)
{
}

bool CNpcInteraction::checkNav(const CMenuAction& nav) const
{
    return nav == _nav;
}

CMenuAction CNpcInteraction::nav(CMenu& menu)
{
    makeNav(menu);
    return _nav;
}

nlohmann::json CNpcInteraction::save() const
{
    return nlohmann::json();
}

void CNpcInteraction::load(const nlohmann::json&)
{
}

std::string CNpcInteraction::translatorObjectName() const
{
    return std::string(TagNames::Translator::npcInteraction);
}

std::string CNpcInteraction::translatorModuleName() const
{
    return std::string(TagNames::Translator::core);
}
