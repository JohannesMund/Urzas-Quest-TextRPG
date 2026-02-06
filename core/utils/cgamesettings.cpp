#include "cgamesettings.h"
#include "clog.h"
#include "defaultsettings.h"
#include "localdirectory.h"
#include "json/jsonexceptions.h"
#include "json/jsontagnames.h"

#include <fstream>

CGameSettings::CGameSettings() : CJsonDocument(Settings::settingsFileName, TagNames::FileSpec::typeSettings)
{
    try
    {
        load();
    }
    catch (const std::exception&)
    {
        // We can ignore exceptions here
    }
}

std::vector<std::string_view> CGameSettings::supportedLanguages() const
{
    return Settings::supportedLanguages;
}

std::string CGameSettings::currentLanguage() const
{
    return get(TagNames::GameSettings::currentLanguage, std::string(Config::currentLanguage));
}
void CGameSettings::setCurrentLanguage(const std::string_view& lang)
{
    addObject(TagNames::GameSettings::currentLanguage, lang);
    dump();
}

int CGameSettings::maxHp() const
{
    return get(TagNames::GameSettings::maxHp, Config::maxHp);
}

int CGameSettings::maxHpMin() const
{
    return get(TagNames::GameSettings::maxHpMin, Config::maxHpMin);
}

int CGameSettings::gold() const
{
    return get(TagNames::GameSettings::gold, Config::gold);
}

unsigned int CGameSettings::initiative() const
{
    return get(TagNames::GameSettings::initiative, Config::initiative);
}

bool CGameSettings::superCowPowers() const
{
    return get(TagNames::GameSettings::superCowPowers, Config::superCowPowers);
}

unsigned int CGameSettings::turnsUntilShopRefresh() const
{
    return get(TagNames::GameSettings::turnsUntilShopRefresh, Config::turnsUntilShopRefresh);
}

unsigned int CGameSettings::numberOfTowns() const
{
    return get(TagNames::GameSettings::numberOfTowns, Config::numberOfTowns);
}

unsigned int CGameSettings::fieldWidth() const
{
    return get(TagNames::GameSettings::fieldWidth, Config::fieldWidth);
}

unsigned int CGameSettings::fieldHeight() const
{
    return get(TagNames::GameSettings::fieldHeight, Config::fieldHeight);
}

unsigned int CGameSettings::encounterChance() const
{
    return get(TagNames::GameSettings::encounterChance, Config::encounterChance);
}

unsigned int CGameSettings::fightChance() const
{
    return get(TagNames::GameSettings::fightChance, Config::fightChance);
}

int CGameSettings::informationCost() const
{
    return get(TagNames::GameSettings::informationCost, Config::informationCost);
}
