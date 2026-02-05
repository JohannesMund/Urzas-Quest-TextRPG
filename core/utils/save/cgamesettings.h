#pragma once

#include <nlohmann/json.hpp>

class CGameSettings
{
public:
    static CGameSettings* Settings()
    {
        static CGameSettings s;
        return &s;
    }

    std::vector<std::string_view> supportedLanguages() const;
    std::string_view currentLanguage() const;
    void setCurrentLanguage(const std::string_view& lang);

    void reloadSettings();

    int maxHp() const;
    int maxHpMin() const;
    int gold() const;
    unsigned int initiative() const;
    bool superCowPowers() const;

    unsigned int turnsUntilShopRefresh() const;
    unsigned int numberOfTowns() const;
    unsigned int fieldWidth() const;
    unsigned int fieldHeight() const;

    unsigned int encounterChance() const;
    unsigned int fightChance() const;
    int informationCost() const;

private:
    CGameSettings();

    void dump();
    bool settingsAvailable();

    nlohmann::json _settings;
};