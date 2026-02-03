#include "ccavedungeonmap.h"
#include "cdungeonroom.h"
#include "moduleressources.h"

CCaveDungeonMap::CCaveDungeonMap(const unsigned int width, const unsigned int height) : CDungeonMap(width, height)
{
}

CDungeonRoom* CCaveDungeonMap::makeDefaultRoom() const
{
    auto dungeonRoom = new CDungeonRoom();
    dungeonRoom->setDescription(Cave::getRandomDescription());
    dungeonRoom->setModuleName(Cave::moduleName());
    return dungeonRoom;
}
