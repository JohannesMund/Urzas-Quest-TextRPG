#include "sroomcoords.h"

void Map::SRoomCoords::transpose(const Core::EDirections dir)
{
    switch (dir)
    {
    case Core::EDirections::eNorth:
        y--;
        break;
    case Core::EDirections::eEast:
        x++;
        break;
    case Core::EDirections::eSouth:
        y++;
        break;
    case Core::EDirections::eWest:
        x--;
        break;
    default:
        break;
    }
}
