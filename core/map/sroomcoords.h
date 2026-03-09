#pragma once

#include "core.h"

namespace Map
{
struct SRoomCoords
{
    unsigned int x;
    unsigned int y;

    bool operator==(const SRoomCoords& other) const
    {
        return x == other.x && y == other.y;
    }

    void transpose(const Core::EDirections dir);
};
} // namespace Map
