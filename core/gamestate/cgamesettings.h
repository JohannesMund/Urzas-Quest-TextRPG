#pragma once

#include "json/cjsondocument.h"

#include <nlohmann/json.hpp>

/**
 * @brief CGamesSettings Represent the Settings file
 * @sa CJsonDocument
 * @remark throws exceptions
 * @remark created and accessed by CGameManagement
 */

class CGameSettings : public CJsonDocument
{
public:
    /**
     * Comes with its own Singleton because it must be loaded before the GameManagement
     */
    static CGameSettings* Settings()
    {
        static CGameSettings s;
        return &s;
    }

    /**
     * Getter / Setter for all settings that are relevant with default values
     * @sa core/defaultsettings.h
     * @sa core/ressources/settings.json for an example file
     * @remark settings are dnumped whenever a setter is called
     */

    static std::vector<std::string_view> supportedLanguages();
    static bool isSourceLanguage(const std::string_view& lang);
    static bool isSupportedLanguage(const std::string_view& lang);

    std::string currentLanguage() const;
    void setCurrentLanguage(const std::string_view& lang);

    bool superCowPowers() const;
    bool updateTranslations() const;

    int maxHp() const;
    int maxHpMin() const;
    int gold() const;
    unsigned int initiative() const;

    unsigned int turnsUntilShopRefresh() const;
    unsigned int numberOfTowns() const;
    unsigned int fieldWidth() const;
    unsigned int fieldHeight() const;

    unsigned int encounterChance() const;
    unsigned int fightChance() const;
    int informationCost() const;

private:
    nlohmann::json getDebugObject() const;

    CGameSettings();
};