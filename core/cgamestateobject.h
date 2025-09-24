#pragma once
#include "save/jsontagnames.h"

#include <nlohmann/json_fwd.hpp>
#include <string>

/**
 * @brief base class for every class that represents part of the state of the game
 * @remark every class derieved from this class can be stored and restored to a json file
 */
class CGameStateObject
{
public:
    /**
     * @brief Contructor Adds an object name to match an object in the savegame to a class
     * @remark Must be a unique name for each class.
     * @remark Every base class must implement this.
     */
    CGameStateObject(const std::string_view& objectName);

    /**
     * @brief returns the object name
     * @remark used by the factories to restore the class instances from the save game
     */
    std::string getObjectName() const;

    /**
     * @brief to be implemented by every game state object
     * @return a json object with the state of the class
     */
    virtual nlohmann::json save() const = 0;
    virtual void load(const nlohmann::json&)
    {
        return;
    };

    static std::string getObjectNameFromJson(const nlohmann::json& json);
    static void addObjectNameToJson(nlohmann::json& json, const CGameStateObject* object);

    static bool compareObjectName(const std::string_view& objectName, const nlohmann::json& json);

private:
    const std::string _objectName;
};