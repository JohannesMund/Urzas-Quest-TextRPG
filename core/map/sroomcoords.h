#pragma once

#include "core.h"

namespace Map
{

/**
 * @brief SRoomCoords A Struct representing coordinates
 * used in the whole Map-context
 */

struct SRoomCoords
{
    unsigned int x;
    unsigned int y;

    bool operator==(const SRoomCoords& other) const
    {
        return x == other.x && y == other.y;
    }

    /**
     * @brief transpose
     * move 1 unit in a certain direction
     * @param[in] dir direction
     */
    void transpose(const Core::EDirections dir);
};
} // namespace Map
