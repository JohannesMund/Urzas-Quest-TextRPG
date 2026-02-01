#pragma once
#include "cencounter.h"
#include "cmap.h"
#include "ctask.h"
#include "roomfactory.h"

#include <string>

class CGameStateObject;
class CRoom : public CGameStateObject
{
public:
    friend CRoom* RoomFactory::loadRoomFromSaveGame(const nlohmann::json& json);

    CRoom(const std::string_view& objectName);
    virtual ~CRoom();

    void blockPath(const CMap::EDirections dir, const bool block);

    bool north() const;
    bool east() const;
    bool south() const;
    bool west() const;

    bool seen() const;
    virtual void setSeen(const bool b);

    bool showInFogOfWar() const;

    char mapSymbol() const;

    virtual std::string bgColor() const;
    virtual std::string fgColor() const;

    virtual void execute();

    void setTask(CTask* task);
    CTask* takeTask();
    virtual bool isTaskPossible(const std::string_view& = {}) const;
    bool hasTask() const;

    virtual bool isSpecialRoom() const;
    virtual bool isEmptyRoom() const;

protected:
    virtual char getMapSymbol() const = 0;

    void executeTask();

    bool _pathNorth = true;
    bool _pathEast = true;
    bool _pathSouth = true;
    bool _pathWest = true;

    bool _showInFogOfWar = false;
    bool _seen = false;
    std::string _description;

    CTask* _task = nullptr;
    bool _isRandomTaskPossible = true;

    CEncounter::EEncounterType _encounterType;
    std::string _moduleName;

    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

    virtual std::string coreTr(const std::string_view& textId) const override;
};
