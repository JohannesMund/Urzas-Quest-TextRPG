#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;
class CGameStateObject;
class CSaveFile
{
public:
    static bool saveGameAvailable();

    CSaveFile();

    void addGameObject(const CGameStateObject& obj);
    void addGameObject(const CGameStateObject* obj);
    static void addGameObject(json& gameObjectArray, const CGameStateObject* obj);

    bool dump();

private:
    void addObject(const std::string& key, const json& object);
    json _saveGame;
};