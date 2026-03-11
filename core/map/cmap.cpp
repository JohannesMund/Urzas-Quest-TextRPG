#include "cmap.h"
#include "cave/ccave.h"
#include "ccapital.h"
#include "cgamemanagement.h"
#include "cinjuredpet.h"
#include "clog.h"
#include "colorize.h"
#include "console.h"
#include "croom.h"
#include "csavefile.h"
#include "cstartingroom.h"
#include "ctask.h"
#include "ctown.h"
#include "randomizer.h"
#include "ressources.h"
#include "roomfactory.h"
#include "translator/ctranslator.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <ranges>

const std::map<Core::EDirections, std::string> CMap::_dirMap = {{Core::EDirections::eNorth, "North"},
                                                                {Core::EDirections::eSouth, "South"},
                                                                {Core::EDirections::eWest, "West"},
                                                                {Core::EDirections::eEast, "East"},
                                                                {Core::EDirections::eNone, "None"}};

CMap::CMap(const unsigned int width, const unsigned int height) : CGameStateObject(TagNames::Map::map)
{
    _map.resize({width, height});
}

CMap::~CMap()
{
    for (auto& room : _map)
    {
        if (room != nullptr)
        {
            delete room;
        }
    }
}

void CMap::init(std::vector<CRoom*>& rooms)
{
    rooms.push_back(RoomFactory::makeInjuredPet());
    rooms.push_back(RoomFactory::makeCapital());

    auto startingRoom = new CStartingRoom();
    rooms.push_back(startingRoom);

    const auto numberOfTowns = CGameManagement::getGameSettingsInstance()->numberOfTowns();
    const auto fieldWidth = CGameManagement::getGameSettingsInstance()->fieldWidth();
    const auto fieldHeight = CGameManagement::getGameSettingsInstance()->fieldHeight();

    for (unsigned int i = 0; i < numberOfTowns; i++)
    {
        rooms.push_back(RoomFactory::makeTown());
    }

    while (rooms.size() < (fieldWidth * fieldHeight))
    {
        rooms.push_back(RoomFactory::makeRoom());
    }

    std::shuffle(rooms.begin(), rooms.end(), std::default_random_engine(Randomizer::getRandomEngineSeed()));

    for (const auto room : rooms)
    {
        _map.push_back(room);
    }

    _playerPosition = _map.coordsOf(startingRoom).value();
}

Core::EDirections CMap::string2Direction(const std::string_view s)
{
    auto it = std::find_if(_dirMap.begin(), _dirMap.end(), [&s](const auto p) { return p.second == s; });
    if (it != _dirMap.end())
    {
        return it->first;
    }

    return Core::EDirections::eNone;
}

std::string_view CMap::direction2String(const Core::EDirections d)
{
    return _dirMap.at(d);
}

void CMap::setStartingPosition(const Map::SRoomCoords& coords)
{
    if (coordsValid(coords))
    {
        _playerPosition = coords;
    }
}

void CMap::movePlayer(const Core::EDirections dir)
{
    if (dir == Core::EDirections::eNone)
    {
        return;
    }

    Map::SRoomCoords coords(_playerPosition);

    if (dir == Core::EDirections::eNorth)
    {
        coords.y--;
    }
    if (dir == Core::EDirections::eEast)
    {
        coords.x++;
    }
    if (dir == Core::EDirections::eSouth)
    {
        coords.y++;
    }
    if (dir == Core::EDirections::eWest)
    {
        coords.x--;
    }

    if (coordsValid(coords))
    {
        _playerPosition = coords;
    }
}

bool CMap::coordsValid(const Map::SRoomCoords& coords) const
{
    if (coords.x < 0 || coords.x >= _map.virtualSize().width)
    {
        return false;
    }

    if (coords.y < 0 || coords.y >= _map.virtualSize().height)
    {
        return false;
    }

    return true;
}

bool CMap::navAvailable(const Core::EDirections dir) const
{
    return navAvailable(_playerPosition, dir);
}

bool CMap::navAvailable(const Map::SRoomCoords& coords, const Core::EDirections dir) const
{
    auto room = roomAt(coords);
    if (!room.has_value() || *room == nullptr)
    {
        return false;
    }

    auto transposedCoords(coords);
    transposedCoords.transpose(dir);

    auto nextRoom = roomAt(transposedCoords);
    if (!nextRoom.has_value() || *nextRoom == nullptr)
    {
        return false;
    }

    switch (dir)
    {
    case Core::EDirections::eNorth:
        return (*room)->north() && (*nextRoom)->south();
    case Core::EDirections::eEast:
        return (*room)->east() && (*nextRoom)->west();
    case Core::EDirections::eSouth:
        return (*room)->south() && (*nextRoom)->north();
    case Core::EDirections::eWest:
        return (*room)->west() && (*nextRoom)->east();
    default:
        return false;
    }

    return false;
}

void CMap::printRoom(const Map::SRoomCoords& coords, const int line)
{
    using namespace std;

    auto room = roomAt(coords);
    if (!room.has_value() || (*room) == nullptr)
    {
        cout << "   ";
        return;
    }

    bool left = navAvailable(coords, Core::EDirections::eWest);
    bool bottom = navAvailable(coords, Core::EDirections::eSouth);

    if ((*room)->seen() == false)
    {
        const auto roomLeft = roomAt(coords, Core::EDirections::eWest);
        bool leftSeen = roomLeft.has_value() && *roomLeft != nullptr && (*roomLeft)->seen();

        const auto roomBottom = roomAt(coords, Core::EDirections::eSouth);
        bool bottomSeen = roomBottom.has_value() && *roomBottom != nullptr && (*roomBottom)->seen();

        if (line == 1)
        {
            cout << string{!left && leftSeen ? "|" : " "};

            if ((*room)->showInFogOfWar())
            {
                cout << mapSymbol(coords);
            }
            else
            {
                cout << " ";
            }
            cout << " ";
        }

        if (line == 2)
        {
            cout << string{!left && leftSeen ? "|" : !bottom && bottomSeen ? "_" : " "};
            cout << string{!bottom && bottomSeen ? "__" : "  "};
        }
    }
    else
    {
        cout << (*room)->bgColor();
        if (line == 1)
        {
            cout << string{left ? " " : "|"};
            cout << (*room)->fgColor() << mapSymbol(coords) << CC::ccReset() << (*room)->bgColor();
            cout << " ";
        }

        if (line == 2)
        {
            cout << string{left ? bottom ? " " : "_" : "|"};
            cout << string{bottom ? "  " : "__"};
        }
        cout << CC::ccReset();
    }
}

void CMap::printMap()
{
    if (!_map.virtualSize())
    {
        return;
    }

    for (unsigned int x = 0; x < _map.actualSize().width; x++)
    {
        auto room = roomAt({x, 0});
        if (room.has_value() && room != nullptr && (*room)->seen())
        {
            if (x == 0)
            {
                std::cout << " __";
            }
            else
            {
                std::cout << "___";
            }
        }
        else
        {
            std::cout << "   ";
        }
    }
    std::cout << std::endl;

    for (unsigned int y = 0; y < _map.actualSize().height; y++)
    {
        for (auto i : {1, 2})
        {
            for (unsigned int x = 0; x < _map.actualSize().width; x++)
            {
                printRoom({x, y}, i);
            }

            auto room = roomAt({(unsigned)_map.actualSize().width - 1, y});
            if (room.has_value() && room != nullptr && (*room)->seen())
            {
                std::cout << "|" << std::endl;
            }
            else
            {
                std::cout << " " << std::endl;
            }
        }
    }
}

std::string CMap::mapSymbol(const Map::SRoomCoords& coords)
{
    if (coords == _playerPosition)
    {
        return "X";
    }

    auto room = roomAt(coords);
    if (room.has_value() && (*room) != nullptr)
    {

        return {(*room)->mapSymbol()};
    }

    return " ";
}

std::vector<CRoom*> CMap::roomsMatchingFilter(RoomFilter filter) const
{
    std::vector<CRoom*> rooms;
    for (const auto& room : _map | std::views::filter(filter))
    {
        rooms.push_back(room);
    }

    return rooms;
}

CRoom* CMap::currentRoom() const
{
    return roomAt(_playerPosition).value();
}

void CMap::setTaskToRandomRoom(CTask* task, RoomFilter filter)
{
    std::vector<CRoom*> possibleRooms;
    for (const auto& room : _map | std::views::filter(filter))
    {
        if (room->isTaskPossible(task->moduleName()))
        {
            possibleRooms.push_back(room);
        }
    }

    if (possibleRooms.size() == 0)
    {
        CLog::error() << "CMap: trying to a task on a room, but no room available" << std::endl << std::flush;
        return;
    }

    std::shuffle(
        possibleRooms.begin(), possibleRooms.end(), std::default_random_engine(Randomizer::getRandomEngineSeed()));
    possibleRooms.at(0)->setTask(task);

    if (task->isMovable())
    {
        _movingTasks.push_back(_map.coordsOf(possibleRooms.at(0)).value());
    }
}

void CMap::replaceRandomRoom(CRoom* newRoom)
{
    std::vector<CRoom*> possibleRooms;
    for (const auto& room : _map | std::views::filter([](const auto& room) { return room->canBeReplaced(); }))
    {
        possibleRooms.push_back(room);
    }

    if (possibleRooms.size() == 0)
    {
        CLog::error() << "CMap: trying to replace a room, but no replaceable room available" << std::endl << std::flush;
        return;
    }

    std::shuffle(
        possibleRooms.begin(), possibleRooms.end(), std::default_random_engine(Randomizer::getRandomEngineSeed()));
    auto roomToBeReplaced = possibleRooms.at(0);

    if (std::find(_map.begin(), _map.end(), roomToBeReplaced) != _map.end())
    {
        std::replace(_map.begin(), _map.end(), roomToBeReplaced, newRoom);
        delete roomToBeReplaced;
        return;
    }
}

nlohmann::json CMap::save() const
{
    nlohmann::json mapState;
    mapState[TagNames::Map::playerPosition] = {{TagNames::Common::x, _playerPosition.x},
                                               {TagNames::Common::y, _playerPosition.y}};

    nlohmann::json rooms = nlohmann::json::array();

    for (auto room : _map)
    {
        CSaveFile::addGameObject(rooms, room);
    }

    mapState[TagNames::Map::rooms] = rooms;

    for (const auto coord : _movingTasks)
    {
        nlohmann::json o;
        o[TagNames::Common::x] = coord.x;
        o[TagNames::Common::y] = coord.y;
        mapState[TagNames::Map::movingTasks].push_back(o);
    }

    return mapState;
}

void CMap::load(const nlohmann::json& json)
{
    _playerPosition.x = 0;
    _playerPosition.y = 0;
    if (json.contains(TagNames::Map::playerPosition))
    {
        _playerPosition.x = json[TagNames::Map::playerPosition].value<unsigned int>(TagNames::Common::x, 0);
        _playerPosition.y = json[TagNames::Map::playerPosition].value<unsigned int>(TagNames::Common::y, 0);
    }

    if (json.contains(TagNames::Map::rooms))
    {
        _map.clear();
        for (const auto& room : json[TagNames::Map::rooms])
        {
            auto r = RoomFactory::loadRoomFromSaveGame(room);
            if (r != nullptr)
            {
                _map.push_back(r);
            }
        }
    }
    if (json.contains(TagNames::Map::movingTasks))
    {
        for (const auto& coord : json[TagNames::Map::movingTasks])
        {
            _movingTasks.push_back({coord[TagNames::Common::x], coord[TagNames::Common::y]});
        }
    }
}

std::optional<CRoom*> CMap::roomAt(const Core::EDirections dir) const
{
    return roomAt(_playerPosition, dir);
}

std::optional<CRoom*> CMap::roomAt(const Map::SRoomCoords& coords) const
{
    if (!coordsValid(coords))
    {
        return {};
    }

    return _map.at(coords);
}

std::optional<CRoom*> CMap::roomAt(const Map::SRoomCoords& coords, const Core::EDirections dir) const
{
    Map::SRoomCoords transposedCoords(coords);
    transposedCoords.transpose(dir);
    return roomAt(transposedCoords);
}

std::string CMap::translatorObjectName() const
{
    return std::string(TagNames::Map::map);
}

std::string CMap::translatorModuleName() const
{
    return std::string();
}

void CMap::moveTasks()
{
    _moveCycle++;
    if (_moveCycle > 2)
    {
        _moveCycle = 0;
        return;
    }
    if (_moveCycle != 0)
    {
        return;
    }

    if (_movingTasks.empty())
    {
        return;
    }

    std::vector<Map::SRoomCoords> newPositions;
    for (auto coords : _movingTasks)
    {
        auto room = roomAt(coords);

        if (!room.has_value())
        {
            continue;
        }

        if (!(*room)->hasTask())
        {
            continue;
        }

        std::vector<Core::EDirections> possibilities;
        for (auto dir :
             {Core::EDirections::eEast, Core::EDirections::eSouth, Core::EDirections::eWest, Core::EDirections::eNorth})
        {
            auto newRoom = roomAt(coords, dir);
            if (!newRoom.has_value())
            {
                continue;
            }

            if ((*newRoom)->isTaskPossible())
            {
                possibilities.push_back(dir);
            }
        }

        if (possibilities.empty())
        {
            newPositions.push_back(coords);
            continue;
        }

        std::shuffle(
            possibilities.begin(), possibilities.end(), std::default_random_engine(Randomizer::getRandomEngineSeed()));

        auto dir = possibilities.at(0);
        auto newRoom = roomAt(coords, dir);

        (*newRoom)->setTask((*room)->takeTask());
        auto newCoords = coords;
        newCoords.transpose(dir);
        newPositions.push_back(newCoords);
    }

    _movingTasks = newPositions;
}

Map::SRoomCoords CMap::getPlayerPosition() const
{
    return _playerPosition;
}
