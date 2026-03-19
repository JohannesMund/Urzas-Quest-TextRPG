#pragma once

#include <functional>
#include <map>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <vector>

#include "cgamestateobject.h"
#include "cmapgrid.h"
#include "core.h"
#include "sroomcoords.h"

class CRoom;
class CTask;

/**
 * @brief CMap represents the map
 * used primarily for the overworld
 * @remarks used as base class for the dungeon maps
 * @sa CMapGrid
 */

class CMap : public CGameStateObject
{
public:
    /**
     * type definition for room filter
     */
    using RoomFilter = std::function<bool(const CRoom* room)>;

    /**
     * @brief Constructor / Destructor
     */
    CMap(const unsigned int width, const unsigned int height);
    virtual ~CMap();

    /**
     * @brief init
     * initializes the map with random rooms
     */
    virtual void init(std::vector<CRoom*>& rooms);

    /**
     * @brief setStartingPosition
     * Sets the starting position of the player
     */
    void setStartingPosition(const Map::SRoomCoords& coords);

    /**
     * @brief movePlayer
     * Moves the player 1 field in a given direction
     */
    void movePlayer(const Core::EDirections dir);

    /**
     * @brief getPlayerPosition
     * returns the current position of the player on the map
     * @sa currentRoom()
     */
    Map::SRoomCoords getPlayerPosition() const;

    /**
     * @brief currentRoom
     * returns the room the player is currently located
     * @sa getPlayerPosition()
     */
    CRoom* currentRoom() const;

    /**
     * @brief setTaskToRandomRoom
     * finds a room on the map to place a specific task on
     * @sa CRoom::isTaskPossible()
     */
    void setTaskToRandomRoom(CTask* task, RoomFilter filter = [](const CRoom*) { return true; });

    /**
     * @brief replaceRandomRoom
     * finds a random room to be replaced with a given room
     * @sa CRoom::isReplacable()
     */
    void replaceRandomRoom(CRoom* newRoom);

    /**
     * @brief moveTasks
     * moves all Tasks that are movable
     * @sa CTask::taskMovement()
     */
    void moveTasks();

    /**
     * @brief coordsValid
     * checks whether given coords are valid
     */
    bool coordsValid(const Map::SRoomCoords& coords) const;
    /**
     * @brief navAvailable
     * checks, whether a given nac is available
     */
    bool navAvailable(const Core::EDirections dir) const;
    bool navAvailable(const Map::SRoomCoords& coords, const Core::EDirections dir) const;

    /**
     * @brief printRoom
     * prints the room at given coords
     * @param[in] coords the coords of the room
     * @param[in] line each room is printed over 2 lines
     */
    void printRoom(const Map::SRoomCoords& coords, const int line);

    /**
     * @brief printMap
     * prints the whole map
     */
    void printMap();

    /**
     * @brief mapSymbol
     * returns the colorized map symbol of the room at coords
     */
    std::string mapSymbol(const Map::SRoomCoords& coords);

    /**
     * @brief roomsMatchingFilter
     * returns all rooms matching a given filter
     * @sa RoomFilter
     */
    std::vector<CRoom*> roomsMatchingFilter(RoomFilter filter) const;

    /**
     * @brief load/save
     * loads or saves the map
     */
    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

protected:
    CMapGrid<CRoom*> _map;
    std::optional<CRoom*> roomAt(const Core::EDirections dir) const;
    std::optional<CRoom*> roomAt(const Map::SRoomCoords& coords) const;
    std::optional<CRoom*> roomAt(const Map::SRoomCoords& coords, const Core::EDirections dir) const;

    Map::SRoomCoords _playerPosition;

    static const std::string saveObjectName;
    virtual std::string translatorObjectName() const override;
    virtual std::string translatorModuleName() const override;

private:
    void moveTask(CRoom* room);
};
