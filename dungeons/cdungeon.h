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

    void setMapRooom(CRoom* mapRoom);

    /**
     * @brief creates a healing well room
     * @remark room is not added to the dungeon, but has to bee added to the init function
     * @sa init()
     * @param description description of the room
     * @param question question "Do you want to try"
     * @param effect effect when player uses the healing room
     * @return a pointer to a new healing well
     */
    static CRoom* makeHealingWell(const std::string& description,
                                  const std::string& question,
                                  const std::string& effect);

    /**
     * @brief makeMapRoom adds a map room
     * @remark room is not added to the dungeon, but has to bee added to the init function
     * @sa init()
     * @param description
     * @return a pointer to a new dungeon map room
     */
    static CRoom* makeMapRoom(const std::string& description);

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
