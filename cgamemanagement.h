#pragma once

#include "ccompanion.h"
#include "cencounter.h"
#include "cgameprogression.h"
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
    static CGameProgression* getProgressionInstance();

    void placeTaskOnField(CTask* task);
    void placeTaskOnTown(CTask* task);

    void executeRandomEncounter(const CEncounter::EEncounterType type, const std::string& moduleName = {}) const;
    void registerEncounter(CEncounter* encounter);
    void unregisterEncounterByModuleName(const std::string_view& name);

    CRoom* currentRoom() const;

    void printHUD();

private:
    void start();

    void executeTurn();
    void handlePlayerDeath();

    void init();
    void gameLoop();
    void lookForTrouble();

    CPlayer* getPlayer();
    CInventory* getInventory();
    CCompanion* getCompanion();
    CGameProgression* getProgression();

    CGameManagement();
    ~CGameManagement();

    CMap _map;
    CPlayer _player;
    CInventory _inventory;
    CGameProgression _progression;

    CCompanion* _companion;

    bool _isGameOver = false;
    std::vector<CEncounter*> _encounters;
};
