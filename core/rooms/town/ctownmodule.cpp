#include "ctownmodule.h"

void CTownModule::setCityName(const std::string& s)
{
    _cityName = s;
}

std::string CTownModule::translatorObjectName() const
{
    return std::string(TagNames::Translator::town);
}

std::string CTownModule::translatorModuleName() const
{
    return std::string(TagNames::Translator::core);
}

nlohmann::json CTownModule::save() const
{
    return nlohmann::json();
}

void CTownModule::load(const nlohmann::json&)
{
}

CMenuAction CTownModule::townModuleNav(CMenu& menu) const
{
    return menu.createAction({"Blacksmith"});
}

CTownModule::CTownModule(const std::string_view& objectName) : CGameStateObject(objectName)
{
}
