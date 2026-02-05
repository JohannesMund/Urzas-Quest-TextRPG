#include "cgamesettings.h"
#include "clog.h"
#include "defaults.h"
#include "defaultsettings.h"
#include "localdirectory.h"
#include "save/saveexceptions.h"
#include "savetagnames.h"

#include <fstream>

CGameSettings::CGameSettings()
{
    reloadSettings();
}

std::vector<std::string_view> CGameSettings::supportedLanguages() const
{
    return Settings::supportedLanguages;
}

std::string_view CGameSettings::currentLanguage() const
{
    if (_settings.contains(TagNames::GameSettings::currentLanguage))
        return _settings[TagNames::GameSettings::currentLanguage];
    return Config::currentLanguage;
}
void CGameSettings::setCurrentLanguage(const std::string_view& lang)
{
    _settings[TagNames::GameSettings::currentLanguage] = lang;
    dump();
}

void CGameSettings::reloadSettings()
{
    try
    {
        if (!settingsAvailable())
        {
            _settings = nlohmann::json();
        }

        auto path = LocalDirectory::getLocalDirectoryPath();
        path.append(Settings::settingsFileName);

        std::ifstream f;
        f.open(path);
        if (!f.is_open())
        {
            throw SaveFile::CSaveFileException(std::format("Read file {} failed", path.string()));
        }
        _settings = nlohmann::json::parse(f)[TagNames::GameSettings::gameSettings];
        f.close();
    }
    catch (const SaveFile::CSaveFileException& e)
    {
        CLog::error() << "Error loading settings " << e.what() << std::endl << std::flush;
    }
    catch (const nlohmann::json::exception& e)
    {
        CLog::error() << "Error loading settings " << e.what() << std::endl << std::flush;
    }
}

int CGameSettings::maxHp() const
{
    if (_settings.contains(TagNames::GameSettings::maxHp))
        return _settings[TagNames::GameSettings::maxHp];
    return Config::maxHp;
}

int CGameSettings::maxHpMin() const
{
    if (_settings.contains(TagNames::GameSettings::maxHpMin))
        return _settings[TagNames::GameSettings::maxHpMin];
    return Config::maxHpMin;
}

int CGameSettings::gold() const
{
    if (_settings.contains(TagNames::GameSettings::gold))
        return _settings[TagNames::GameSettings::gold];
    return Config::gold;
}

unsigned int CGameSettings::initiative() const
{
    if (_settings.contains(TagNames::GameSettings::initiative))
        return _settings[TagNames::GameSettings::initiative];
    return Config::initiative;
}

bool CGameSettings::superCowPowers() const
{
    if (_settings.contains(TagNames::GameSettings::superCowPowers))
        return _settings[TagNames::GameSettings::superCowPowers];
    return Config::superCowPowers;
}

unsigned int CGameSettings::turnsUntilShopRefresh() const
{
    if (_settings.contains(TagNames::GameSettings::turnsUntilShopRefresh))
        return _settings[TagNames::GameSettings::turnsUntilShopRefresh];
    return Config::turnsUntilShopRefresh;
}

unsigned int CGameSettings::numberOfTowns() const
{
    if (_settings.contains(TagNames::GameSettings::numberOfTowns))
        return _settings[TagNames::GameSettings::numberOfTowns];
    return Config::numberOfTowns;
}

unsigned int CGameSettings::fieldWidth() const
{
    if (_settings.contains(TagNames::GameSettings::fieldWidth))
        return _settings[TagNames::GameSettings::fieldWidth];
    return Config::fieldWidth;
}

unsigned int CGameSettings::fieldHeight() const
{
    if (_settings.contains(TagNames::GameSettings::fieldHeight))
        return _settings[TagNames::GameSettings::fieldHeight];
    return Config::fieldHeight;
}

unsigned int CGameSettings::encounterChance() const
{
    if (_settings.contains(TagNames::GameSettings::encounterChance))
        return _settings[TagNames::GameSettings::encounterChance];
    return Config::encounterChance;
}

unsigned int CGameSettings::fightChance() const
{
    if (_settings.contains(TagNames::GameSettings::fightChance))
        return _settings[TagNames::GameSettings::fightChance];
    return Config::fightChance;
}

int CGameSettings::informationCost() const
{
    if (_settings.contains(TagNames::GameSettings::informationCost))
        return _settings[TagNames::GameSettings::informationCost];
    return Config::informationCost;
}

void CGameSettings::dump()
{
    nlohmann::json fl;
    fl[TagNames::FileSpec::fileSpec] =
        nlohmann::json({{TagNames::FileSpec::name, "UrzasQuest TextRPG"},
                        {TagNames::FileSpec::version, 1},
                        {TagNames::FileSpec::fileType, TagNames::FileSpec::typeSettings}});
    auto now = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
    fl[TagNames::FileSpec::dateTime] = std::format("{:%Y-%m-%d %H:%M:%S}", now);
    fl[TagNames::GameSettings::gameSettings] = _settings;

    try
    {
        auto path = LocalDirectory::getLocalDirectoryPath();
        path.append(Settings::settingsFileName);
        std::ofstream f;
        f.open(path, std::ofstream::out | std::ofstream::trunc);
        if (!f.is_open())
        {
            throw SaveFile::CSaveFileException(std::format("Write file {} failed", path.string()));
        }
        f << fl.dump(2).c_str() << std::flush;
        f.close();
    }
    catch (const SaveFile::CSaveFileException& e)
    {
        CLog::error() << "Error dumping settings " << e.what() << std::endl << std::flush;
    }
    catch (const nlohmann::json::exception& e)
    {
        CLog::error() << "Error dumping settings " << e.what() << std::endl << std::flush;
    }
}

bool CGameSettings::settingsAvailable()
{
    try
    {
        auto path = LocalDirectory::getLocalDirectoryPath();
        path.append(Settings::settingsFileName);
        return std::filesystem::exists(path);
    }
    catch (const SaveFile::CSaveFileException&)
    {
        return false;
    }

    return false;
}
