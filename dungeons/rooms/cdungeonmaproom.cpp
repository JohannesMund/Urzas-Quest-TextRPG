#include "cdungeonmaproom.h"

CDungeonMapRoom::CDungeonMapRoom() : CDungeonRoom()
{
}

void CDungeonMapRoom::execute()
{
    CDungeonRoom::execute();
    _isMapRevealed = true;
}

std::string CDungeonMapRoom::mapSymbol() const
{
    return "m";
}

bool CDungeonMapRoom::isSpecialRoom() const
{
    return true;
}

bool CDungeonMapRoom::isMapRevealed() const
{
    return _isMapRevealed;
}
