#include "cdungeonmaproom.h"

CDungeonMapRoom::CDungeonMapRoom() : CDungeonRoom()
{
}

void CDungeonMapRoom::execute()
{
    CDungeonRoom::execute();
    _isMapRevealed = true;
}

bool CDungeonMapRoom::isSpecialRoom() const
{
    return true;
}

bool CDungeonMapRoom::isMapRevealed() const
{
    return _isMapRevealed;
}

std::string CDungeonMapRoom::translatorModuleName() const
{
    return std::string();
}

char CDungeonMapRoom::getMapSymbol() const
{
    return 'm';
}
