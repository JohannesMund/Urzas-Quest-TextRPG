#pragma once

#include <nlohmann/json.hpp>

class CGameStateObject;

/**
 * @brief represents a save game
 * @remark provides a check whether a save game file is available
 * @remark uses a file in the local directory
 * @sa save/localDirectory.h
 * @remark throws exceptions
 * @sa save/exceptions.h CSaveFileException
 *
 */
class CSaveFile
{
public:
    /**
     * @brief is a save game available?
     * @remark just looks in the destination folder whether there is a file with the right name
     * @remark does not throw exceptions, if an error occurs, it is asumed, that no saveGame exists
     */
    static bool saveGameAvailable();

    CSaveFile();

    /**
     * @brief adds a game state object  to the save file
     * @remark key name is the objectName of obj
     */
    void addGameObject(const CGameStateObject* obj);

    /**
     * @brief loads a game object from json
     * @remark calls the load() from the game object.
     * @remark game object must be initialized
     */
    void loadGameObject(CGameStateObject* obj);

    /**
     * @brief adds a game state object a given array
     * @remark adds the objectName to the obj
     */
    static void addGameObject(nlohmann::json& gameObjectArray, const CGameStateObject* obj);

    /**
     * @brief writes the save game
     * @remark existing file is overwritten
     */
    void dump();

    /**
     * @brief loads a save game
     */
    void load();

    nlohmann::json root() const;

private:
    void addObject(const std::string_view& key, const nlohmann::json& object);
    nlohmann::json getObject(const std::string_view& key);
    nlohmann::json _saveGame;
};