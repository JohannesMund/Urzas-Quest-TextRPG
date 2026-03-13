#pragma once

#include <functional>
#include <map>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <vector>

#include "cgamestateobject.h"
#include "cmapgrid.h"
#include "core.h"
#include "sroomcoords.h"

class CRoom;
class CTask;
class CMap : public CGameStateObject
{
public:
    static const std::map<Core::EDirections, std::string> _dirMap;

    using RoomFilter = std::function<bool(const CRoom* room)>;

    static Core::EDirections string2Direction(const std::string_view s);
    static std::string_view direction2String(const Core::EDirections d);

    CMap(const unsigned int width, const unsigned int height);
    virtual ~CMap();

    virtual void init(std::vector<CRoom*>& rooms);

    void setStartingPosition(const Map::SRoomCoords& coords);
    void movePlayer(const Core::EDirections dir);
    Map::SRoomCoords getPlayerPosition() const;
    bool coordsValid(const Map::SRoomCoords& coords) const;
    bool navAvailable(const Core::EDirections dir) const;
    bool navAvailable(const Map::SRoomCoords& coords, const Core::EDirections dir) const;

    void printRoom(const Map::SRoomCoords& coords, const int line);
    void printMap();
    std::string mapSymbol(const Map::SRoomCoords& coords);

    std::vector<CRoom*> roomsMatchingFilter(RoomFilter filter) const;
    CRoom* currentRoom() const;

    void setTaskToRandomRoom(CTask* task, RoomFilter filter = [](const CRoom*) { return true; });

    void replaceRandomRoom(CRoom* newRoom);

    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

    void moveTasks();

protected:
    CMapGrid<CRoom*> _map;
    std::optional<CRoom*> roomAt(const Core::EDirections dir) const;
    std::optional<CRoom*> roomAt(const Map::SRoomCoords& coords) const;
    std::optional<CRoom*> roomAt(const Map::SRoomCoords& coords, const Core::EDirections dir) const;

    Map::SRoomCoords _playerPosition;

    static const std::string saveObjectName;
    virtual std::string translatorObjectName() const override;
    virtual std::string translatorModuleName() const override;

private:
    void moveTask(CRoom* room);
};
