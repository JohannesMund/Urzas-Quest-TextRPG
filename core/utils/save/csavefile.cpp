#include "csavefile.h"
#include "cgamestateobject.h"
#include "console.h"
#include "defaultsettings.h"
#include "exceptions.h"
#include "globals.h"
#include "localdirectory.h"
#include "ressources.h"
#include "saveexceptions.h"

#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>

CSaveFile::CSaveFile()
{
    addObject(TagNames::FileSpec::fileSpec,
              {{TagNames::FileSpec::name, "UrzasQuest TextRPG"},
               {TagNames::FileSpec::version, 1},
               {TagNames::FileSpec::fileType, TagNames::FileSpec::typeSave}});

    nlohmann::json gameState;
    auto now = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
    gameState[TagNames::FileSpec::dateTime] = std::format("{:%Y-%m-%d %H:%M:%S}", now);
    addObject("GameState", gameState);
}

bool CSaveFile::saveGameAvailable()
{
    try
    {
        auto path = LocalDirectory::getLocalDirectoryPath();
        path.append(Settings::saveFileName);
        return std::filesystem::exists(path);
    }
    catch (const SaveFile::CSaveFileException&)
    {
        return false;
    }
}

void CSaveFile::addGameObject(const CGameStateObject* obj)
{
    if (obj == nullptr)
    {
        return;
    }
    addObject(obj->getObjectName(), obj->save());
}

void CSaveFile::loadGameObject(CGameStateObject* obj)
{
    try
    {
        auto val = getObject(obj->getObjectName());
        obj->load(val);
    }
    catch (const SaveFile::CSaveFileException& e)
    {
        throw e;
    }
}

void CSaveFile::addGameObject(nlohmann::json& gameObjectArray, const CGameStateObject* obj)
{
    auto o = obj->save();
    CGameStateObject::addObjectNameToJson(o, obj);
    gameObjectArray.push_back(o);
}

void CSaveFile::dump()
{
    try
    {
        auto path = LocalDirectory::getLocalDirectoryPath();
        path.append(Settings::saveFileName);
        std::ofstream f;
        f.open(path, std::ofstream::out | std::ofstream::trunc);
        if (!f.is_open())
        {
            throw SaveFile::CSaveFileException(std::format("Write file {} failed", path.string()));
        }
        f << _saveGame.dump(2).c_str() << std::flush;
        f.close();
    }
    catch (const SaveFile::CSaveFileException& e)
    {
        throw e;
    }
    catch (const nlohmann::json::exception& e)
    {
        throw SaveFile::CSaveFileException(e);
    }
}

void CSaveFile::load()
{
    try
    {
        if (!saveGameAvailable())
        {
            throw SaveFile::CSaveFileException("No savegame available");
        }

        auto path = LocalDirectory::getLocalDirectoryPath();
        path.append(Settings::saveFileName);

        std::ifstream f;
        f.open(path);
        if (!f.is_open())
        {
            throw SaveFile::CSaveFileException(std::format("Read file {} failed", path.string()));
        }
        _saveGame = nlohmann::json::parse(f);
        f.close();
    }
    catch (const SaveFile::CSaveFileException& e)
    {
        throw e;
    }
    catch (const nlohmann::json::exception& e)
    {
        throw SaveFile::CSaveFileException(e);
    }
}

nlohmann::json CSaveFile::root() const
{
    return _saveGame;
}

void CSaveFile::addObject(const std::string_view& key, const nlohmann::json& object)
{
    _saveGame[key] = object;
}

nlohmann::json CSaveFile::getObject(const std::string_view& key)
{
    try
    {
        if (_saveGame.contains(key))
        {
            return _saveGame[key];
        }
    }
    catch (const nlohmann::json::exception& e)
    {
        throw SaveFile::CSaveFileException(e);
        return {};
    }

    throw SaveFile::CSaveFileException(std::format("Key not found: {}", key));
    return {};
}
