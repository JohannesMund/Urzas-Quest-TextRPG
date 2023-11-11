#pragma once

#include <cdungeonroom.h>

/**
 * @brief The CDungeonRoomNoRoom class
 * a blank room, that cannot be entered, used to have no nullptr in the dungeon map and hav correct dungeon walls
 */

class CDungeonRoomNoRoom : public CDungeonRoom
{
public:
    CDungeonRoomNoRoom();

    /**
     * @brief setSeen sets the room as seen
     * @param b ignored, CDungeonRoomNoRoom cannot be visible
     * @sa CRoom::setSeen
     */
    virtual void setSeen(const bool b) override;

    virtual bool isSpecialRoom() const override;
    virtual bool isEmptyRoom() const override;
};
