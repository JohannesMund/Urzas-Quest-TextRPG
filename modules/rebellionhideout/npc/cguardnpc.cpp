#include "cguardnpc.h"

#include "cbattleinteraction.h"
#include "colorize.h"
#include "core.h"
#include "rebellionhideout/moduleressources.h"

CGuardNpc::CGuardNpc(const std::string_view& name) :
    CNpc(TagNames::RebellionHideout::guardNpc, Core::EGender::eMale),
    _name(name)
{
    addInteraction(new CBattleInteraction(this));
}

void CGuardNpc::interact()
{
    CNpc::interact();
    CMenuAction input;

    do
    {
        CMenu menu(RebellionHideout::moduleName());
        input = CNpc::executeNpcMenu(menu);
    } while (input != CMenu::exit());
}

void CGuardNpc::talk()
{
}

std::string CGuardNpc::name() const
{
    return _name;
}

std::string CGuardNpc::describe() const
{
    return std::string();
}

nlohmann::json CGuardNpc::save() const
{
    auto json = CNpc::save();
    json[TagNames::Common::name] = _name;
    return json;
}

void CGuardNpc::load(const nlohmann::json& json)
{
    CNpc::load(json);
    _name = json[TagNames::Common::name];
}

std::string CGuardNpc::translatorModuleName() const
{
    return RebellionHideout::moduleName();
}

void CGuardNpc::printHeader(const bool) const
{
}
