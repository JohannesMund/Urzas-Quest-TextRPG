#include "ccave.h"
#include "ccavebosstask.h"
#include "ccavedungeon.h"
#include "ccavedungeonmap.h"
#include "chealingwell.h"
#include "cmenu.h"
#include "colorconsole.h"
#include "console.h"
#include "moduleressources.h"

CCave::CCave()
{
    _showInFogOfWar = true;
    _encounterType = CEncounter::EEncounterType::eNone;
    _isTaskPossible = false;
}

void CCave::execute()
{
    Console::printLn("There is a cave, do you want to have a look?");
    if (CMenu::executeYesNoMenu() == CMenu::yes())
    {
        std::vector<CRoom*> rooms;
        rooms.push_back(CDungeon::makeHealingWell(CaveRessources::getWellDescription(1),
                                                  CaveRessources::getWellQuestion(1),
                                                  CaveRessources::getWellEffect(1)));

        rooms.push_back(CDungeon::makeHealingWell(CaveRessources::getWellDescription(2),
                                                  CaveRessources::getWellQuestion(2),
                                                  CaveRessources::getWellEffect(2)));

        rooms.push_back(CDungeon::makeHealingWell(CaveRessources::getWellDescription(3),
                                                  CaveRessources::getWellQuestion(3),
                                                  CaveRessources::getWellEffect(3)));

        auto mapRoom = CDungeon::makeMapRoom(CaveRessources::getMapRoomDescription());
        rooms.push_back(static_cast<CRoom*>(mapRoom));

        CCaveDungeonMap map(25, 10);
        map.setStartingPosition({0, 0});
        map.init(rooms);

        CCaveDungeon dungeon;
        dungeon.setDungeonMap(&map);
        dungeon.setMapRooom(mapRoom);

        dungeon.execute();
    }

    CField::execute();
}

std::string CCave::mapSymbol() const
{
    return "C";
}
