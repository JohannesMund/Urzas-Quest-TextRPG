#pragma once

#include "cdungeonmap.h"

class CRoom;
class CDungeonMapRoom;

/**
 * @brief The CDungeon class
 * Class to handle dungeons.
 * Any Encounter / Task / room, etc can instantiate and execute a dungeon
 * must be derieved to be used.
 */

class CDungeon
{
public:
    /**
     * @brief CDungeon Constructor
     */
    CDungeon();
    virtual ~CDungeon()
    {
    }

    /**
     * @brief execute
     * must be implemented. Init a dungeon map and call dungeonLoop
     * @sa CDungeonMap
     * @sa dungeonLoop
     */
    virtual void execute() = 0;

    /**
     * @brief loopHook
     * must be implemented. Called everytime a new loop is started
     * @sa dungeonLoop()
     */
    virtual void loopHook() = 0;

    /**
     * @brief setDungeonMap
     * Sets the dungeon Map
     * @param map
     */
    void setDungeonMap(CDungeonMap* map);

    CRoom* makeHealingWell(const std::string& description, const std::string& question, const std::string& effect);
    CRoom* makeMapRoom(const std::string& description);

protected:
    /**
     * @brief dungeonLoop
     * Handles the execution of the dungeon. blocks, until the dungeon is finished
     * @param map
     */
    void dungeonLoop();

    CDungeonMap* _map;
    CDungeonMapRoom* _mapRoom = nullptr;
};
