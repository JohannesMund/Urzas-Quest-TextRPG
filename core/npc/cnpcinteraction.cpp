#include "cnpcinteraction.h"

#include "cgamemanagement.h"
#include "cmenu.h"
#include "cnpc.h"

#include <nlohmann/json.hpp>

CNpcInteraction::CNpcInteraction(CNpc* npc, const std::string_view& objectName) :
    CGameStateObject(objectName),
    _npc(npc)
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

void CNpcInteraction::executeInteraction()
{
    _lastExecuted = CGameManagement::getProgressionInstance()->turns();
}

bool CNpcInteraction::interactionAvailable() const
{
    return (CGameManagement::now() - _lastExecuted) > _cooldown;
}

nlohmann::json CNpcInteraction::save() const
{
    nlohmann::json json;
    json[TagNames::NpcInteractions::cooldown] = _cooldown;
    return json;
}

void CNpcInteraction::load(const nlohmann::json& json)
{
    _cooldown = json[TagNames::NpcInteractions::cooldown];
}

std::string CNpcInteraction::translatorObjectName() const
{
    return std::string(TagNames::Translator::npcInteraction);
}

std::string CNpcInteraction::translatorModuleName() const
{
    return std::string(TagNames::Translator::core);
}
