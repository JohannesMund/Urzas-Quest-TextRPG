#pragma once

#include "cmap.h"

#include <optional>
#include <vector>

class CRoom;
class CDungeonRoom;

/**
 * @brief The CDungeonMap class
 * represents the map of a dungeon. initialiszes the dungeon randomly
 */

class CDungeonMap : public CMap
{
public:
    /**
     * @brief CDungeonMap Constructor
     * @param width width of the dungeon
     * @param height height of the dungeon
     */
    CDungeonMap(const unsigned int width, const unsigned int height);

    /**
     * @brief init populates the dungeon randomly.
     * call, the have the dungeon filled
     * override, to replace certain rooms
     */
    virtual void init(std::vector<CRoom*>& rooms) override;

    /**
     * @brief reveal
     * Sets all DungeonRooms to _seen=true;
     * CDungeonRoomNoRoom ignores that
     * @sa CDungeonRoomNoRoom
     */
    void reveal();

    /**
     * @brief roomCount
     * @return the count of visitable rooms
     */
    unsigned int roomCount() const;

    /**
     * @brief seenRooms
     * @return the count of visited rooms
     */
    unsigned int seenRooms() const;

    /**
     * @brief addSpecificRoom
     * Adds a specific room to a random position
     * @remark room will be deleted automatically
     * @param room the room to add
     */
    void addSpecificRoom(CDungeonRoom* room);

    /**
     * @brief addTask
     * Adds a Task to a random room
     * @param task the task to be added
     * @param isMovingTask if true, the task will move when moveTasks is called
     * @sa moveTasks()
     */
    void addTask(CTask* task, const bool isMovingTask = false);

    /**
     * @brief moveTasks
     * moves all tasks that are added as moving tasks 1 field if possible
     */
    void moveTasks();

    /**
     * @brief isMapRevealed
     * @return  true, if the map has been revealed
     */
    bool isMapRevealed() const;

    /**
     * @brief isExitAvailable
     * @return true, if exit is available
     * @remark the map itself will not activate the exit
     * @sa setExitAvailable
     */
    bool isExitAvailable() const;

    /**
     * @brief setExitAvailable
     * activates the exit
     */
    void setExitAvailable();

protected:
    /**
     * @brief makeDefaultRoom
     * used by init()
     * override to fill the dungeon with custom rooms
     * @sa init()
     * @return a default dungeon room
     */
    virtual CDungeonRoom* makeDefaultRoom() const = 0;

    /**
     * @brief makeNoRoom
     * @return returns a blank field, that cannot be entered
     */
    CDungeonRoom* makeNoRoom() const;

private:
    CMap::SRoomCoords getRandomRoomCoords(const bool noSpecialRooms = true, const bool notPlayerPosition = true);

    void makeNextRoom(const CMap::SRoomCoords coords, std::vector<CRoom*>& rooms);

    void fillWithNoRooms();

    unsigned int _populatedRoomCount = 0;
    unsigned int _specialRoomCount = 0;
    bool _isMapRevealed = false;
    bool _isExitAvailable = false;

    std::vector<CMap::SRoomCoords> _movingTasks;
};
