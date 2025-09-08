#pragma once

#include <nlohmann/json.hpp>

class CGameStateObject;

/**
 * @brief represents a save game
 * @remark provides a check whether a save game file is available
 */
class CSaveFile
{
public:
    /**
     * @brief is a save game available?
     * @remark just looks in the destination folder whether there is a file with the right name
     */
    static bool saveGameAvailable();

    CSaveFile();

    /**
     * @brief adds a game state object  to the save file
     * @remark key name is the objectName of obj
     */
    void addGameObject(const CGameStateObject& obj);
    void addGameObject(const CGameStateObject* obj);

    /**
     * @brief adds a game state object a given array
     * @remark adds the objectName to the obj
     */
    static void addGameObject(nlohmann::json& gameObjectArray, const CGameStateObject* obj);

    /**
     * @brief writes the save game
     * @remark existing file is overwritten
     */
    bool dump();

private:
    void addObject(const std::string& key, const nlohmann::json& object);
    nlohmann::json _saveGame;
};