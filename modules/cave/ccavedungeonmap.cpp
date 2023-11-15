#include "ccavedungeonmap.h"
#include "cdungeonroom.h"
#include "moduleressources.h"

CCaveDungeonMap::CCaveDungeonMap(const unsigned int width, const unsigned int height) : CDungeonMap(width, height)
{
}

CDungeonRoom* CCaveDungeonMap::makeDefaultRoom() const
{
    auto dungeonRoom = new CDungeonRoom();
    dungeonRoom->setDescription(CaveRessources::getRandomDescription());
    dungeonRoom->setModuleName(CaveRessources::moduleName());
    return dungeonRoom;
}
