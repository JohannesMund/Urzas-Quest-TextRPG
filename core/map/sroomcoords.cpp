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

void Map::SRoomCoords::transpose(const Core::EAlignment dir, const bool min)
{
    if (min)
    {
        dec(dir);
    }
    else
    {
        inc(dir);
    }
}

void Map::SRoomCoords::inc(const Core::EAlignment dir)
{
    if (dir == Core::EAlignment::eHorizontal)
    {
        x++;
    }
    else
    {
        y++;
    }
}

void Map::SRoomCoords::dec(const Core::EAlignment dir)
{
    if (dir == Core::EAlignment::eHorizontal)
    {
        x--;
    }
    else
    {
        y--;
    }
}