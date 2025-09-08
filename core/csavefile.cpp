#include "csavefile.h"
#include "cgamestateobject.h"
#include "console.h"
#include "globals.h"
#include "localdirectory.h"
#include "ressources.h"

#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>

CSaveFile::CSaveFile()
{
    addObject("FSpec", {{"Name", "UrzasQuest TextRPG"}, {"version", 1}});

    json gameState;
    auto now = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
    gameState["DateTime"] = std::format("{:%Y-%m-%d %H:%M:%S}", now);
    addObject("GameState", gameState);
}

bool CSaveFile::saveGameAvailable()
{
    bool ok;
    auto path = LocalDirectory::getLocalDirectoryPath(ok);
    if (!ok)
    {
        return false;
    }

    path.append(Ressources::Settings::saveFileName);
    return std::filesystem::exists(path);
}

void CSaveFile::addGameObject(const CGameStateObject& obj)
{
    addObject(obj.getObjectName(), obj.save());
}

void CSaveFile::addGameObject(const CGameStateObject* obj)
{
    if (obj == nullptr)
    {
        return;
    }
    addObject(obj->getObjectName(), obj->save());
}

void CSaveFile::addGameObject(json& gameObjectArray, const CGameStateObject* obj)
{
    auto o = obj->save();
    o["ClassName"] = obj->getObjectName();
    gameObjectArray.push_back(o);
}

bool CSaveFile::dump()
{
    bool ok;
    auto path = LocalDirectory::getLocalDirectoryPath(ok);
    if (!ok)
    {
        Console::printLn("Error getting local directory");
        return false;
    }

    path.append(Ressources::Settings::saveFileName);

    std::ofstream f;
    f.open(path, std::ofstream::out | std::ofstream::trunc);
    if (!f.is_open())
    {
        Console::printLn(std::format("Write file {} failed", path.string()));
        return false;
    }
    f << _saveGame.dump(2).c_str() << std::flush;
    f.close();
    return true;
}

void CSaveFile::addObject(const std::string& key, const json& object)
{
    _saveGame[key] = object;
}
