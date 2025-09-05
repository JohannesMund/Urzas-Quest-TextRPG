#pragma once
#include <nlohmann/json.hpp>

using json = nlohmann::json;
class CSaveFile
{
public:
    CSaveFile();
    static bool saveGameAvailable();
    bool dump();

private:
    void addObject(const std::string& key, const json& object);

    json _saveGame;
};