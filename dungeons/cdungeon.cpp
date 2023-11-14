#include "cdungeon.h"
#include "cdungeonmaproom.h"
#include "cgamemanagement.h"
#include "chealingwell.h"
#include "cmenu.h"
#include "colorconsole.h"
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

void CDungeon::addHealingWell(const std::string& description, const std::string& question, const std::string& effect)
{
    CHealingWell* well = new CHealingWell();
    well->setDescription(description);
    well->setQuestion(question);
    well->setEffect(effect);
    _map->addSpecificRoom(well);
}

void CDungeon::addMapRoom(const std::string& description)
{
    CDungeonMapRoom* mapRoom = new CDungeonMapRoom();
    mapRoom->setDescription(description);
    _map->addSpecificRoom(mapRoom);
    _mapRoom = mapRoom;
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
        if (CGameManagement::getPlayerInstance()->isDead())
        {
            return;
        }

        CMenu menu;
        std::vector<CMenu::Action> navs;
        for (auto nav : _map->getDirectionNavs())
        {
            navs.push_back(menu.createAction(nav));
        }

        menu.addMenuGroup(navs, {menu.createAction("Map"), menu.createAction("Inventory")});

        std::vector<CMenu::Action> exitActionHalf = {};
        if (_map->isExitAvailable())
        {
            exitActionHalf.push_back(CMenu::exit());
        }

        menu.addMenuGroup({menu.createAction("Reveal")}, exitActionHalf);

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
                Console::confirmToContinue();
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
                Console::confirmToContinue();
            }
            if (input == CMenu::exit())
            {
                return;
            }
        }
    }
}
