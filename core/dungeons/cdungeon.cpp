#include "cdungeon.h"
#include "cdungeonmaproom.h"
#include "cgamemanagement.h"
#include "chealingwell.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "cplayer.h"
#include "croom.h"

CDungeon::CDungeon()
{
}

void CDungeon::setDungeonMap(CDungeonMap* map)
{
    _map = map;
}

void CDungeon::setMapRooom(CRoom* mapRoom)
{
    auto r = dynamic_cast<CDungeonMapRoom*>(mapRoom);
    if (r != nullptr)
    {
        _mapRoom = r;
    }
}

CRoom* CDungeon::makeHealingWell(const std::string& description, const std::string& question, const std::string& effect)
{
    CHealingWell* well = new CHealingWell();
    well->setDescription(description);
    well->setQuestion(question);
    well->setEffect(effect);
    return well;
}

CRoom* CDungeon::makeMapRoom(const std::string& description)
{
    CDungeonMapRoom* mapRoom = new CDungeonMapRoom();
    mapRoom->setDescription(description);
    return mapRoom;
}

void CDungeon::dungeonLoop()
{
    while (true)
    {
        if (!_map->isMapRevealed() && _mapRoom != nullptr && _mapRoom->isMapRevealed())
        {
            _map->reveal();
        }

        Console::cls();
        loopHook();

        _map->currentRoom()->execute();

        CMenu menu;
        CMenu::ActionList navs;

        CMenuAction northAction = menu.createAction({std::string(CMap::direction2String(CMap::EDirections::eNorth))});
        if (_map->navAvailable(CMap::EDirections::eNorth))
        {
            navs.push_back(northAction);
        }

        CMenuAction eastAction = menu.createAction({std::string(CMap::direction2String(CMap::EDirections::eEast))});
        if (_map->navAvailable(CMap::EDirections::eEast))
        {
            navs.push_back(eastAction);
        }

        CMenuAction southAction = menu.createAction({std::string(CMap::direction2String(CMap::EDirections::eSouth))});
        if (_map->navAvailable(CMap::EDirections::eSouth))
        {
            navs.push_back(southAction);
        }

        CMenuAction westAction = menu.createAction({std::string(CMap::direction2String(CMap::EDirections::eWest))});
        if (_map->navAvailable(CMap::EDirections::eWest))
        {
            navs.push_back(westAction);
        }

        CMenuAction mapAction = menu.createAction({"Map"});
        CMenuAction inventoryAction = menu.createAction({"Inventory"});

        menu.addMenuGroup(navs, {mapAction, inventoryAction});

        CMenu::ActionList exitActionHalf = {};
        if (_map->isExitAvailable())
        {
            exitActionHalf.push_back(CMenu::exit());
        }

        CMenu::ActionList superCowHalf = {};
        CMenuAction revealAction = menu.createAction({"Reveal"});
        if (CGameManagement::getGameSettingsInstance()->superCowPowers())
        {
            superCowHalf.push_back(revealAction);
        }

        menu.addMenuGroup(superCowHalf, exitActionHalf);

        while (true)
        {
            auto input = menu.execute();

            if (input == northAction)
            {
                _map->movePlayer(CMap::EDirections::eNorth);
                break;
            }
            if (input == eastAction)
            {
                _map->movePlayer(CMap::EDirections::eEast);
                break;
            }
            if (input == southAction)
            {
                _map->movePlayer(CMap::EDirections::eSouth);
                break;
            }
            if (input == westAction)
            {
                _map->movePlayer(CMap::EDirections::eWest);
                break;
            }

            if (input == mapAction)
            {
                Console::cls();
                _map->printMap();
            }
            if (input == inventoryAction)
            {
                Console::cls();
                CGameManagement::getInventoryInstance()->print(CInventory::Scope::eList);
            }
            if (input == revealAction)
            {
                Console::cls();
                _map->reveal();
                _map->printMap();
            }
            if (input == CMenu::exit())
            {
                return;
            }
        }
    }
}
