#include "cgamemanagement.h"
#include "cbattleencounter.h"
#include "cdeadhero.h"
#include "cencounter.h"
#include "cfield.h"
#include "cgameprogression.h"
#include "citemfactory.h"
#include "cmenu.h"
#include "cmysteriouschest.h"
#include "companionfactory.h"
#include "console.h"
#include "croom.h"
#include "ctask.h"
#include "ctown.h"
#include "randomizer.h"
#include "rebellionhideout/cbagofingredients.h"

#include <iostream>
#include <string>
#include <vector>

CGameManagement* _instance = nullptr;

CGameManagement* CGameManagement::getInstance()
{
    if (_instance == nullptr)
    {
        static CGameManagement instance;
        _instance = &instance;
        _instance->start();
    }

    return _instance;
}

CPlayer* CGameManagement::getPlayerInstance()
{
    return getInstance()->getPlayer();
}

CInventory* CGameManagement::getInventoryInstance()
{
    return getInstance()->getInventory();
}

CCompanion* CGameManagement::getCompanionInstance()
{
    return getInstance()->getCompanion();
}

CGameProgression* CGameManagement::getProgressionInstance()
{
    return getInstance()->getProgression();
}

CItemFactory* CGameManagement::getItemFactoryInstance()
{
    return getInstance()->getItemFactory();
}

void CGameManagement::placeTask(CTask* task, CMap::RoomFilter filter)
{
    _map.setTaskToRandomRoom(task, filter);
}

void CGameManagement::placeTaskOnField(CTask* task)
{
    _map.setTaskToRandomRoom(task, CField::fieldFilter());
}

void CGameManagement::placeTaskOnTown(CTask* task)
{
    _map.setTaskToRandomRoom(task, CTown::townFilter());
}

void CGameManagement::start()
{
    init();
    gameLoop();
}

void CGameManagement::executeRandomEncounter(const CEncounter::EEncounterType type, const std::string& moduleName) const
{
    if (_encounters.size() == 0)
    {
        return;
    }

    if (Randomizer::getRandom(100) > Ressources::Config::encounterChance)
    {
        return;
    }

    std::vector<unsigned int> indices;

    for (unsigned int index = 0; index < _encounters.size(); index++)
    {
        auto encounter = _encounters.at(index);
        if (encounter->canBeExecuted(type) == false)
        {
            continue;
        }

        auto chance = encounter->encounterChance(type, moduleName);
        if (chance == 0)
        {
            continue;
        }
        for (unsigned int i = 0; i < chance; i++)
        {
            indices.push_back(index);
        }
    }

    if (indices.size() == 0)
    {
        return;
    }

    std::shuffle(indices.begin(), indices.end(), std::default_random_engine(Randomizer::getRandomEngineSeed()));
    _encounters.at(indices.at(0))->execute(moduleName);
    Console::confirmToContinue();
}

void CGameManagement::registerEncounter(CEncounter* encounter)
{
    _encounters.push_back(encounter);
}

void CGameManagement::unregisterEncounterByModuleName(const std::string_view& name)
{
    auto filterAndRemove = [&name](CEncounter* e)
    {
        auto filter = CEncounter::moduleNameFilter(name);
        if (filter(e))
        {
            delete e;
            return true;
        }
        return false;
    };

    auto it = std::remove_if(_encounters.begin(), _encounters.end(), filterAndRemove);

    if (it != _encounters.end())
    {
        _encounters.erase(it);
    }
}

CRoom* CGameManagement::currentRoom() const
{
    return _map.currentRoom();
}

std::vector<CRoom*> CGameManagement::roomsMatchingFilter(CMap::RoomFilter filter) const
{
    return _map.roomsMatchingFilter(filter);
}

CPlayer* CGameManagement::getPlayer()
{
    return &_player;
}

CInventory* CGameManagement::getInventory()
{
    return &_inventory;
}

CCompanion* CGameManagement::getCompanion()
{
    return _companion;
}

CGameProgression* CGameManagement::getProgression()
{
    return &_progression;
}

CItemFactory* CGameManagement::getItemFactory()
{
    return &_itemFactory;
}

void CGameManagement::printHUD()
{
    Console::hr();
    _player.print();
}

void CGameManagement::executeTurn()
{
    _progression.increaseTurns();
    Console::cls();

    _map.currentRoom()->execute();
    if (_player.isDead())
    {
        return;
    }

    while (true)
    {
        Console::hr();

        CMenu menu;

        CMenu::ActionList navs;
        for (auto nav : _map.getDirectionNavs())
        {
            navs.push_back(menu.createAction(nav));
        }

        menu.addMenuGroup(navs, {menu.createAction("Map"), menu.createAction("Inventory")});

        if (Ressources::Config::superCowPowers)
        {
            menu.addMenuGroup({menu.createAction("Look for trouble")}, {menu.createAction("Quit Game")});
        }
        else
        {
            menu.addMenuGroup({}, {menu.createAction("Quit Game")});
        }

        auto input = menu.execute();
        if (input.key == 'q')
        {
            Console::cls(false);
            Console::hr();
            Console::printLn("Quit game?", Console::EAlignment::eCenter);
            Console::printLn("(No save, no mercy!)", Console::EAlignment::eCenter);
            Console::hr();
            Console::br();
            CMenu menu;
            menu.addMenuGroup({CMenu::yes()}, {CMenu::no()});

            if (menu.execute() == CMenu::yes())
            {
                _isGameOver = true;
                return;
            }
        }

        if (CMap::string2Direction(input.name) != CMap::EDirections::eNone)
        {
            _map.movePlayer(CMap::string2Direction(input.name));
            return;
        }

        if (input.key == 'l')
        {
            lookForTrouble();
            if (_player.isDead())
            {
                return;
            }
            Console::confirmToContinue();
        }
        if (input.key == 'm')
        {
            Console::cls();
            _map.printMap();
        }
        if (input.key == 'i')
        {
            Console::cls();
            _inventory.print(CInventory::Scope::eList);
        }
    }
}

void CGameManagement::handlePlayerDeath()
{
    if (!_player.isDead())
    {
        return;
    }

    auto items = CGameManagement::getInventoryInstance()->getItemsWithDeathEffect();
    for (auto item : items)
    {
        CGameManagement::getInventoryInstance()->useDeathAction(item);
        if (!_player.isDead())
        {
            Console::confirmToContinue();
            return;
        }
    }

    Console::printLn("      _____      ", Console::EAlignment::eCenter);
    Console::printLn(" ____|R.I.P|____ ", Console::EAlignment::eCenter);
    Console::printLn("|   Here lies   |", Console::EAlignment::eCenter);
    Console::printLn("|____ Player____|", Console::EAlignment::eCenter);
    Console::printLn("     |     |     ", Console::EAlignment::eCenter);
    Console::printLn("     |     |     ", Console::EAlignment::eCenter);
    Console::printLn("     |     |     ", Console::EAlignment::eCenter);
    Console::printLn("     |_____|     ", Console::EAlignment::eCenter);

    Console::printLn("- He died the way he lived -", Console::EAlignment::eCenter);
    Console::printLn(" - naked and alone -", Console::EAlignment::eCenter);
}

void CGameManagement::init()
{
    Randomizer::init();

    _inventory.addItem(CGameManagement::getItemFactoryInstance()->makeLootItem());
    _inventory.addItem(CGameManagement::getItemFactoryInstance()->makeLootItem());
    _inventory.addItem(CGameManagement::getItemFactoryInstance()->makeLootItem());
    _inventory.addItem(CGameManagement::getItemFactoryInstance()->makeLootItem());
    _inventory.addItem(CGameManagement::getItemFactoryInstance()->makeLootItem());

    std::vector<CRoom*> rooms;

    _progression.initEncounters();
    _progression.initModules();
    _progression.initWorldMap(rooms);
    _progression.startGame();

    _map.setStartingPosition({3, 5});
    _map.init(rooms);
}

void CGameManagement::gameLoop()
{
    while (!_isGameOver)
    {
        _progression.checkGameProgress();
        executeTurn();
        handlePlayerDeath();
        if (_player.isDead())
        {
            _isGameOver = true;
            return;
        }
    }
}

void CGameManagement::lookForTrouble()
{
    CBattle battle;
    battle.fight();
}

CGameManagement::CGameManagement() :
    _map(CMap(Ressources::Config::fieldWidth, Ressources::Config::fieldHeight)),
    _inventory(&_itemFactory)
{
    _companion = CompanionFactory::makeRandomCompanion();
}

CGameManagement::~CGameManagement()
{
    delete _companion;
    for (auto e : _encounters)
    {
        delete e;
    }
}
