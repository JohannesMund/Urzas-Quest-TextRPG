#include "csewerdungeonmap.h"
#include "cdungeonroom.h"
#include "moduleressources.h"

CSewerDungeonMap::CSewerDungeonMap(const unsigned int width, const unsigned int height) : CDungeonMap(width, height)
{
}

CDungeonRoom* CSewerDungeonMap::makeDefaultRoom() const
{
    auto dungeonRoom = new CDungeonRoom();
    dungeonRoom->setDescription(Sewer::getRandomDescription());
    dungeonRoom->setModuleName(Sewer::moduleName());
    return dungeonRoom;
}
