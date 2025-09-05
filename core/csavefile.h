#pragma once
#include <nlohmann/json.hpp>

using json = nlohmann::json;
class CSaveFile
{
public:
    static bool saveGameAvailable();

    CSaveFile();

    bool dump();

private:
    void addObject(const std::string& key, const json& object);

    json _saveGame;
};