#include "cdungeon.h"
#include "cdungeonmaproom.h"
#include "cgamemanagement.h"
#include "chealingwell.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "core.h"
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
        CGameManagement::getProgressionInstance()->increaseTurns();
        _map->moveTasks();

        if (!_map->isMapRevealed() && _mapRoom != nullptr && _mapRoom->isMapRevealed())
        {
            _map->reveal();
        }

        Console::cls();
        loopHook();

        _map->currentRoom()->execute();

        CMenu menu;
        CMenu::ActionList navs;

        auto northAction = menu.createAction({std::string(CMap::direction2String(Core::EDirections::eNorth))});
        if (_map->navAvailable(Core::EDirections::eNorth))
        {
            navs.push_back(northAction);
        }

        auto eastAction = menu.createAction({std::string(CMap::direction2String(Core::EDirections::eEast))});
        if (_map->navAvailable(Core::EDirections::eEast))
        {
            navs.push_back(eastAction);
        }

        auto southAction = menu.createAction({std::string(CMap::direction2String(Core::EDirections::eSouth))});
        if (_map->navAvailable(Core::EDirections::eSouth))
        {
            navs.push_back(southAction);
        }

        auto westAction = menu.createAction({std::string(CMap::direction2String(Core::EDirections::eWest))});
        if (_map->navAvailable(Core::EDirections::eWest))
        {
            navs.push_back(westAction);
        }

        auto mapAction = menu.createAction({"Map"});
        auto inventoryAction = menu.createAction({"Inventory"});

        menu.addMenuGroup(navs, {mapAction, inventoryAction});

        CMenu::ActionList exitActionHalf = {};
        if (_map->isExitAvailable())
        {
            exitActionHalf.push_back(CMenu::exit());
        }

        CMenu::ActionList superCowHalf = {};
        auto revealAction = menu.createAction({"Reveal"});
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
                _map->movePlayer(Core::EDirections::eNorth);
                break;
            }
            if (input == eastAction)
            {
                _map->movePlayer(Core::EDirections::eEast);
                break;
            }
            if (input == southAction)
            {
                _map->movePlayer(Core::EDirections::eSouth);
                break;
            }
            if (input == westAction)
            {
                _map->movePlayer(Core::EDirections::eWest);
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
