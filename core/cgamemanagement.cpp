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
#include "csavefile.h"
#include "ctask.h"
#include "ctown.h"
#include "exceptions.h"
#include "randomizer.h"
#include "rebellionhideout/cbagofingredients.h"
#include "json/jsonexceptions.h"

#include <format>
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

CGameSettings* CGameManagement::getGameSettingsInstance()
{
    return CGameSettings::Settings();
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

void CGameManagement::loadGameSettings()
{
    //_settings.reloadSettings();
}

void CGameManagement::startGame()
{
    init();
    gameLoop();
}

void CGameManagement::loadGame()
{
    if (load())
    {
        gameLoop();
    }
}

void CGameManagement::executeRandomEncounter(const CEncounter::EEncounterType type, const std::string& moduleName) const
{
    if (_encounters.size() == 0)
    {
        return;
    }

    if (Randomizer::getRandom(100) > CGameSettings::Settings()->encounterChance())
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

    while (true)
    {
        Console::hr();
        CMenu menu;
        CMenu::ActionList navs;

        CMenuAction northAction = menu.createAction(CMap::direction2String(CMap::EDirections::eNorth));
        if (_map.navAvailable(CMap::EDirections::eNorth))
        {
            navs.push_back(northAction);
        }

        CMenuAction eastAction = menu.createAction(CMap::direction2String(CMap::EDirections::eEast));
        if (_map.navAvailable(CMap::EDirections::eEast))
        {
            navs.push_back(eastAction);
        }

        CMenuAction southAction = menu.createAction(CMap::direction2String(CMap::EDirections::eSouth));
        if (_map.navAvailable(CMap::EDirections::eSouth))
        {
            navs.push_back(southAction);
        }

        CMenuAction westAction = menu.createAction(CMap::direction2String(CMap::EDirections::eWest));
        if (_map.navAvailable(CMap::EDirections::eWest))
        {
            navs.push_back(westAction);
        }

        CMenuAction mapAction = menu.createAction("Map");
        CMenuAction inventoryAction = menu.createAction("Inventory");

        menu.addMenuGroup(navs, {mapAction, inventoryAction});

        CMenuAction troubleAction = menu.createAction("Look for trouble");
        CMenuAction quitAction = menu.createAction("Quit Game");

        if (getGameSettingsInstance()->superCowPowers())
        {
            menu.addMenuGroup({troubleAction}, {quitAction});
        }
        else
        {
            menu.addMenuGroup({}, {quitAction});
        }

        auto input = menu.execute();
        if (input == quitAction)
        {
            Console::cls(false);
            Console::hr();
            Console::printLn("Quit game", Console::EAlignment::eCenter);
            Console::printLn("Do you want to save your progress?", Console::EAlignment::eCenter);
            Console::hr();

            CMenu menu;
            CMenuAction saveAction = menu.createAction("Save", 's');
            CMenuAction cancelAction = menu.createAction("Cancel", 'c');
            CMenuAction quitAction = menu.createAction("Quit without saving", 'q');

            menu.addMenuGroup({saveAction, quitAction});
            menu.addMenuGroup({cancelAction});

            auto reply = menu.execute();

            if (reply == quitAction)
            {
                throw CGameOverException();
            }

            if (reply == saveAction && save() == true)
            {
                throw CGameOverException();
            }
            Console::cls();
        }

        if (input == northAction)
        {
            _map.movePlayer(CMap::EDirections::eNorth);
            return;
        }
        if (input == eastAction)
        {
            _map.movePlayer(CMap::EDirections::eEast);
            return;
        }
        if (input == southAction)
        {
            _map.movePlayer(CMap::EDirections::eSouth);
            return;
        }
        if (input == westAction)
        {
            _map.movePlayer(CMap::EDirections::eWest);
            return;
        }

        if (input == troubleAction)
        {
            lookForTrouble();
            if (_player.isDead())
            {
                return;
            }
            Console::confirmToContinue();
        }
        if (input == mapAction)
        {
            Console::cls();
            _map.printMap();
        }
        if (input == inventoryAction)
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
    while (true)
    {
        _progression.checkGameProgress();

        try
        {
            executeTurn();
        }
        catch (const CPlayerDiedException& e)
        {
            handlePlayerDeath();
            if (_player.isDead())
            {
                return;
            }
        }
        catch (const CGameOverException& e)
        {
            return;
        }
    }
}

void CGameManagement::lookForTrouble()
{
    CBattle battle;
    battle.fight();
}

bool CGameManagement::load()
{
    if (!saveGameAvailable())
    {
        return false;
    }
    try
    {
        CSaveFile saveGame;
        saveGame.load();
        saveGame.loadGameObject(&_player);
        saveGame.loadGameObject(&_inventory);

        _progression.initEncounters();
        _progression.initModules();

        saveGame.loadGameObject(&_progression);

        auto c = CompanionFactory::loadCompanionFromSaveGame(saveGame.root());
        if (c != nullptr)
        {
            _companion = c;
        }
        saveGame.loadGameObject(&_map);
    }
    catch (Json::CJsonException& e)
    {
        Console::printErr("Error Loading Savegame", e.what());
        return false;
    }
    return true;
}

bool CGameManagement::saveGameAvailable()
{
    return CSaveFile::saveGameAvailable();
}

bool CGameManagement::save()
{
    if (saveGameAvailable())
    {
        Console::cls(false);
        Console::hr();
        Console::printLn("A save game exists.", Console::EAlignment::eCenter);
        Console::printLn("Overwrite?", Console::EAlignment::eCenter);
        Console::hr();

        if (CMenu::executeYesNoMenu() != CMenu::yes())
        {
            return false;
        }
    }

    try
    {
        CSaveFile savegame;
        savegame.addGameObject(&_player);
        savegame.addGameObject(&_inventory);
        savegame.addGameObject(&_map);
        if (_companion->level() > 0)
        {
            savegame.addGameObject(_companion);
        }
        savegame.addGameObject(&_progression);
        savegame.dump();
    }

    catch (const Json::CJsonException& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}

CGameManagement::CGameManagement() :
    _map(CMap(CGameSettings::Settings()->fieldWidth(), CGameSettings::Settings()->fieldHeight())),
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
