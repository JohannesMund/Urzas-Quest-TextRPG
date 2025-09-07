#include "cdungeonmap.h"
#include "cdungeonmaproom.h"
#include "cdungeonroom.h"
#include "cdungeonroomnoroom.h"
#include "chealingwell.h"
#include "croom.h"
#include "randomizer.h"

#include <algorithm>
#include <cmath>

CDungeonMap::CDungeonMap(const unsigned int width, const unsigned int height) : CMap(width, height)
{
}

void CDungeonMap::init(std::vector<CRoom*>& rooms)
{
    _populatedRoomCount = static_cast<unsigned int>(std::ceil((_map.size() * _map.at(0).size()) / 2));

    while (rooms.size() < _populatedRoomCount)
    {
        rooms.push_back(makeDefaultRoom());
    }

    std::shuffle(rooms.begin(), rooms.end(), std::default_random_engine(Randomizer::getRandomEngineSeed()));

    makeNextRoom(getPlayerPosition(), rooms);

    fillWithNoRooms();
}

void CDungeonMap::makeNextRoom(const SRoomCoords coords, std::vector<CRoom*>& rooms)
{
    _map.at(coords.y).at(coords.x) = rooms.at(rooms.size() - 1);
    rooms.pop_back();

    if (rooms.empty())
    {
        return;
    }

    std::vector<SRoomCoords> possibilities;
    for (const auto dir :
         {CMap::EDirections::eEast, CMap::EDirections::eSouth, CMap::EDirections::eWest, CMap::EDirections::eNorth})
    {
        auto transposedCoords(coords);
        transposedCoords.transpose(dir);
        auto room = roomAt(transposedCoords);
        if (room.has_value() && *room == nullptr)
        {
            possibilities.push_back(transposedCoords);
        }
    }

    if (!possibilities.size())
    {
        return;
    }

    std::shuffle(
        possibilities.begin(), possibilities.end(), std::default_random_engine(Randomizer::getRandomEngineSeed()));

    for (auto c : possibilities)
    {
        makeNextRoom(c, rooms);
        if (rooms.empty())
        {
            return;
        }
    }
}

CDungeonRoom* CDungeonMap::makeNoRoom() const
{
    return new CDungeonRoomNoRoom();
}

CMap::SRoomCoords CDungeonMap::getRandomRoomCoords(const bool noSpecialRooms, const bool notPlayerPosition)
{
    unsigned int roomCount = _populatedRoomCount;
    if (noSpecialRooms)
    {
        roomCount -= _specialRoomCount;
    }
    if (notPlayerPosition)
    {
        roomCount--;
    }

    auto targetRoom = Randomizer::getRandom(roomCount);

    auto counter = 0U;
    for (unsigned int x = 0; x < _map.size(); x++)
    {
        auto line = _map.at(x);

        for (unsigned int y = 0; y < line.size(); y++)
        {
            auto room = _map.at(x).at(y);
            if (room->isEmptyRoom())
            {
                continue;
            }

            if (room->isSpecialRoom() && noSpecialRooms)
            {
                continue;
            }

            if ((SRoomCoords{y, x} == _playerPosition) && notPlayerPosition)
            {
                continue;
            }

            if (counter == targetRoom)
            {
                return {y, x};
            }
            counter++;
        }
    }
    return {};
}

void CDungeonMap::reveal()
{
    for (auto& l : _map)
    {
        for (auto& r : l)
        {
            r->setSeen(true);
        }
    }
    _isMapRevealed = true;
}

unsigned int CDungeonMap::roomCount() const
{
    return _populatedRoomCount;
}

unsigned int CDungeonMap::seenRooms() const
{
    int count = 0;
    for (const auto& line : _map)
    {
        for (const auto& room : line)
        {
            if (room->seen())
            {
                count++;
            }
        }
    }
    return count;
}

void CDungeonMap::addSpecificRoom(CDungeonRoom* room)
{
    auto coords = getRandomRoomCoords();
    if (!coordsValid(coords))
    {
        return;
    }

    delete _map.at(coords.y).at(coords.x);
    _map.at(coords.y).at(coords.x) = room;
    _specialRoomCount++;
}

void CDungeonMap::addTask(CTask* task, const bool isMovingTask)
{
    auto coords = getRandomRoomCoords();
    auto room = roomAt(coords);

    if (!room.has_value())
    {
        return;
    }

    (*room)->setTask(task);
    if (isMovingTask)
    {
        _movingTasks.push_back(coords);
    }
}

void CDungeonMap::moveTasks()
{
    if (_movingTasks.empty())
    {
        return;
    }

    std::vector<CMap::SRoomCoords> newPositions;
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

        std::vector<CMap::EDirections> possibilities;
        for (auto dir :
             {CMap::EDirections::eEast, CMap::EDirections::eSouth, CMap::EDirections::eWest, CMap::EDirections::eNorth})
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

bool CDungeonMap::isMapRevealed() const
{
    return _isMapRevealed;
}

bool CDungeonMap::isExitAvailable() const
{
    return _isExitAvailable;
}

void CDungeonMap::setExitAvailable()
{
    _isExitAvailable = true;
}

void CDungeonMap::fillWithNoRooms()
{
    for (unsigned int x = 0; x < _map.size(); x++)
    {
        auto line = _map.at(x);

        for (unsigned int y = 0; y < line.size(); y++)
        {
            if (_map.at(x).at(y) == nullptr)
            {
                _map.at(x).at(y) = makeNoRoom();
            }
        }
    }
}
