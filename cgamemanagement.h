#pragma once

#include "ccompanion.h"
#include "cencounter.h"
#include "cinventory.h"
#include "cmap.h"
#include "cplayer.h"

#include <string>

class CTask;
class CGameManagement
{
public:
    static CGameManagement* getInstance();
    static CPlayer* getPlayerInstance();
    static CInventory* getInventoryInstance();
    static CCompanion* getCompanionInstance();

    void placeTask(CTask* task);

    void executeRandomEncounter(const CEncounter::EEncounterType type, const std::string& moduleName = {}) const;
    void registerEncounter(CEncounter* encounter);
    void unregisterEncounterByName(const std::string& name);

    CRoom* currentRoom() const;

    void start();

    void printHUD();

private:
    CMap _map;
    CPlayer _player;
    CInventory _inventory;
    CCompanion* _companion;

    std::vector<CEncounter*> _encounters;

    bool _isGameOver = false;
    void printMap();
    void printInventory();

    void executeTurn();
    void handlePlayerDeath();

    void init();
    void gameLoop();
    void lookForTrouble();

    CPlayer* getPlayer();
    CInventory* getInventory();
    CCompanion* getCompanion();

    CGameManagement();
    ~CGameManagement();
};
