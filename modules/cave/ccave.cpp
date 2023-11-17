#include "ccave.h"
#include "ccavebosstask.h"
#include "ccavedungeon.h"
#include "ccavedungeonmap.h"
#include "cgamemanagement.h"
#include "chealingwell.h"
#include "cmenu.h"
#include "colorconsole.h"
#include "console.h"
#include "moduleressources.h"

#include <format>

CCave::CCave()
{
    _showInFogOfWar = true;
    _encounterType = CEncounter::EEncounterType::eNone;
    _isTaskPossible = false;
}

void CCave::execute()
{

    if (CGameManagement::getProgressionInstance()->isModuleActive(CaveRessources::moduleName()))
    {
        Console::printLn(
            "After all your battles and Adventures, you feel confident enought to enter this dark, mysterious cave.");
        Console::printLn("Do you dare to enter?");
        initDungeon();
    }
    else if (CGameManagement::getProgressionInstance()->isModuleActive(CaveRessources::moduleName()))
    {
        Console::printLn(std::format("You remember this cave, you remember {} who lurked inside this cave. You also "
                                     "remember, that this guy should no longer be a problem. Or is he? ",
                                     CaveRessources::getColoredBossString()));
        Console::printLn("Do you want to have a look, whether there is another Boss?");
        initDungeon();
    }
    else
    {
        Console::printLn(
            std::format("On a small hill, there is the entry to a cave. A deep, {}dark {}cave{}. You have a look and "
                        "all you can see is black. A Disgusting smell and strange noises come out of the cave. You "
                        "decide, that you are not enough of a hero to enter this hell hole.",
                        CC::fgLightGray(),
                        CC::fgDarkGray(),
                        CC::ccReset()));
        Console::br();
        Console::confirmToContinue();
        Console::br();
    }

    CField::execute();
}

std::string CCave::mapSymbol() const
{
    return "C";
}

std::string CCave::bgColor() const
{
    return CC::bgBlack();
}

std::string CCave::fgColor() const
{
    return CC::fgDarkGray();
}

void CCave::initDungeon()
{

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
}
