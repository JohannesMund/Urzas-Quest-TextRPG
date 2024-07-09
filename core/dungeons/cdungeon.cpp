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
        for (auto nav : _map->getDirectionNavs())
        {
            navs.push_back(menu.createAction(nav));
        }

        menu.addMenuGroup(navs, {menu.createAction("Map"), menu.createAction("Inventory")});

        CMenu::ActionList exitActionHalf = {};
        if (_map->isExitAvailable())
        {
            exitActionHalf.push_back(CMenu::exit());
        }

        CMenu::ActionList superCowHalf = {};
        if (Ressources::Config::superCowPowers)
        {
            superCowHalf.push_back(menu.createAction("Reveal"));
        }

        menu.addMenuGroup(superCowHalf, exitActionHalf);

        while (true)
        {
            auto input = menu.execute();

            if (CMap::string2Direction(input.name) != CMap::EDirections::eNone)
            {
                _map->movePlayer(CMap::string2Direction(input.name));
                break;
            }

            if (input.key == 'm')
            {
                Console::cls();
                _map->printMap();
            }
            if (input.key == 'i')
            {
                Console::cls();
                CGameManagement::getInventoryInstance()->print(CInventory::Scope::eList);
            }
            if (input.key == 'r')
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
