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
}

void CCave::execute()
{
    Console::printLn("There is a cave, do you want to have a look?");
    if (CMenu::yes(CMenu::executeYesNoMenu()))
    {
        CCaveDungeonMap map(25, 10);
        map.setStartingPosition({0, 0});
        map.init();

        CCaveDungeon dungeon;
        dungeon.setDungeonMap(&map);

        dungeon.addHealingWell(CaveRessources::getWellDescription(1),
                               CaveRessources::getWellQuestion(1),
                               CaveRessources::getWellEffect(1));

        dungeon.addHealingWell(CaveRessources::getWellDescription(2),
                               CaveRessources::getWellQuestion(2),
                               CaveRessources::getWellEffect(2));

        dungeon.addHealingWell(CaveRessources::getWellDescription(3),
                               CaveRessources::getWellQuestion(3),
                               CaveRessources::getWellEffect(3));

        dungeon.addMapRoom(CaveRessources::getMapRoomDescription());

        dungeon.execute();
    }

    CField::execute();
}

std::string CCave::mapSymbol() const
{
    return "C";
}
