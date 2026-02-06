#pragma once

#include "json/cjsondocument.h"

#include <nlohmann/json.hpp>

class CGameSettings : public CJsonDocument
{
public:
    static CGameSettings* Settings()
    {
        static CGameSettings s;
        return &s;
    }

    std::vector<std::string_view> supportedLanguages() const;
    std::string currentLanguage() const;
    void setCurrentLanguage(const std::string_view& lang);

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
};