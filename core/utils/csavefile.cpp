#include "csavefile.h"
#include "cgamestateobject.h"
#include "console.h"
#include "defaultsettings.h"
#include "exceptions.h"
#include "globals.h"
#include "localdirectory.h"
#include "ressources.h"
#include "json/jsonexceptions.h"

#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>

CSaveFile::CSaveFile() : CJsonDocument(Settings::saveFileName, TagNames::FileSpec::typeSave)
{
}

bool CSaveFile::saveGameAvailable()
{
    try
    {
        auto path = LocalDirectory::getLocalDirectoryPath();
        path.append(Settings::saveFileName);
        return std::filesystem::exists(path);
    }
    catch (const Json::CJsonException&)
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
    catch (const Json::CJsonException& e)
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
