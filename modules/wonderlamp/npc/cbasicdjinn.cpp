#include "cbasicdjinn.h"
#include "core.h"
#include "wonderlamp/moduleressources.h"

CBasicDjinn::CBasicDjinn(const Core::EGender gender) : CNpc(TagNames::WonderLamp::djinn, gender)
{
}

void CBasicDjinn::interact()
{
}

nlohmann::json CBasicDjinn::save() const
{
    return nlohmann::json();
}

void CBasicDjinn::load(const nlohmann::json&)
{
}

std::string CBasicDjinn::translatorModuleName() const
{
    return std::string(WonderLamp::moduleName());
}
