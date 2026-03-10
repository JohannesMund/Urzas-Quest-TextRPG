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

    void transpose(const Core::EDirections dir);
    void transpose(const Core::EAlignment dir, const bool min);

    void inc(const Core::EAlignment dir);
    void dec(const Core::EAlignment dir);
};
} // namespace Map
