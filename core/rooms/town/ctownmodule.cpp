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

CTownModule::CTownModule()
{
}
