#include "cmap.h"
#include "cave/ccave.h"
#include "cinjuredpet.h"
#include "colorconsole.h"
#include "console.h"
#include "croom.h"
#include "cshrineoftheancients.h"
#include "cstartingroom.h"
#include "ctask.h"
#include "ctown.h"
#include "randomizer.h"
#include "ressources.h"
#include "roomfactory.h"

#include <algorithm>
#include <iostream>
#include <random>

const std::map<CMap::EDirections, std::string> CMap::_dirMap = {{EDirections::eNorth, "North"},
                                                                {EDirections::eSouth, "South"},
                                                                {EDirections::eWest, "West"},
                                                                {EDirections::eEast, "East"},
                                                                {EDirections::eNone, "None"}};

CMap::CMap(const unsigned int width, const unsigned int height)
{
    for (int x = 0; x < height; x++)
    {
        std::vector<CRoom*> row;

        for (int y = 0; y < width; y++)
        {
            row.push_back(nullptr);
        }

        _map.push_back(row);
    }
}

CMap::~CMap()
{
    for (auto& line : _map)
    {
        for (auto& room : line)
        {
            if (room != nullptr)
            {
                delete room;
            }
        }
    }
}

void CMap::init(std::vector<CRoom*>& rooms)
{
    rooms.push_back(RoomFactory::makeInjuredPet());
    rooms.push_back(RoomFactory::makeShrine());

    for (int i = 0; i < Ressources::Config::numberOfTowns; i++)
    {
        rooms.push_back(RoomFactory::makeTown());
    }

    while (rooms.size() < (Ressources::Config::fieldWidth * Ressources::Config::fieldHeight) - 1)
    {
        rooms.push_back(RoomFactory::makeRoom());
    }

    std::shuffle(rooms.begin(), rooms.end(), std::default_random_engine(Randomizer::getRandomEngineSeed()));

    for (int iRow = 0; iRow < _map.size(); iRow++)
    {
        auto row = _map.at(iRow);
        for (int iCol = 0; iCol < row.size(); iCol++)
        {
            if (iRow == _playerPosition.y && iCol == _playerPosition.x)
            {
                row.at(iCol) = new CStartingRoom();
                continue;
            }

            row.at(iCol) = rooms.at(rooms.size() - 1);
            rooms.pop_back();
        }
        _map.at(iRow) = row;
    }
}

CMap::EDirections CMap::string2Direction(const std::string_view s)
{
    for (const auto& [key, value] : _dirMap)
    {
        if (key != EDirections::eNone && value == s)
        {
            return key;
        }
    }
    return EDirections::eNone;
}

void CMap::setStartingPosition(const SRoomCoords& coords)
{
    if (coordsValid(coords))
    {
        _playerPosition = coords;
    }
}

void CMap::movePlayer(const EDirections dir)
{
    if (dir == EDirections::eNone)
    {
        return;
    }

    SRoomCoords coords(_playerPosition);

    if (dir == EDirections::eNorth)
    {
        coords.y--;
    }
    if (dir == EDirections::eEast)
    {
        coords.x++;
    }
    if (dir == EDirections::eSouth)
    {
        coords.y++;
    }
    if (dir == EDirections::eWest)
    {
        coords.x--;
    }

    if (coordsValid(coords))
    {
        _playerPosition = coords;
    }
}

bool CMap::coordsValid(const SRoomCoords& coords) const
{
    if (coords.x < 0 || coords.x >= _map.at(0).size())
    {
        return false;
    }

    if (coords.y < 0 || coords.y >= _map.size())
    {
        return false;
    }

    return true;
}

bool CMap::navAvailable(const EDirections dir) const
{
    return navAvailable(_playerPosition, dir);
}

bool CMap::navAvailable(const SRoomCoords& coords, const EDirections dir) const
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
    case EDirections::eNorth:
        return (*room)->north() && (*nextRoom)->south();
    case EDirections::eEast:
        return (*room)->east() && (*nextRoom)->west();
    case EDirections::eSouth:
        return (*room)->south() && (*nextRoom)->north();
    case EDirections::eWest:
        return (*room)->west() && (*nextRoom)->east();
    default:
        return false;
    }

    return false;
}

void CMap::printRoom(const SRoomCoords& coords, const int line)
{
    using namespace std;

    auto room = roomAt(coords);
    if (!room.has_value() || (*room) == nullptr)
    {
        cout << "   ";
        return;
    }

    bool left = navAvailable(coords, EDirections::eWest);
    bool bottom = navAvailable(coords, EDirections::eSouth);

    if ((*room)->seen() == false)
    {
        const auto roomLeft = roomAt(coords, EDirections::eWest);
        bool leftSeen = roomLeft.has_value() && *roomLeft != nullptr && (*roomLeft)->seen();

        const auto roomBottom = roomAt(coords, EDirections::eSouth);
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
    if (!_map.size())
    {
        return;
    }

    for (unsigned int x = 0; x < _map.at(0).size(); x++)
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

    for (unsigned int y = 0; y < _map.size(); y++)
    {
        auto line = _map.at(y);

        for (auto i : {1, 2})
        {
            for (unsigned int x = 0; x < line.size(); x++)
            {
                printRoom({x, y}, i);
            }

            auto room = roomAt({(unsigned)line.size() - 1, y});
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

std::vector<std::string_view> CMap::getDirectionNavs()
{
    std::vector<std::string_view> v;

    for (const auto& nav :
         {CMap::EDirections::eNorth, CMap::EDirections::eEast, CMap::EDirections::eSouth, CMap::EDirections::eWest})
    {
        if (navAvailable(nav))
        {
            v.push_back(_dirMap.at(nav));
        }
    }

    return v;
}

std::string CMap::mapSymbol(const SRoomCoords& coords)
{
    if (coords == _playerPosition)
    {
        return "X";
    }

    auto room = roomAt(coords);
    if (room.has_value() && (*room) != nullptr)
    {
        return (*room)->mapSymbol();
    }

    return " ";
}

CRoom* CMap::currentRoom() const
{
    return roomAt(_playerPosition).value();
}

void CMap::setTaskToRandomRoom(CTask* task, const bool fields, const bool towns)
{
    std::vector<CRoom*> possibleRooms;
    for (const auto& row : _map)
    {
        for (auto& room : row)
        {
            if (!fields && dynamic_cast<CField*>(room) != nullptr)
            {
                continue;
            }
            if (!towns && dynamic_cast<CTown*>(room) != nullptr)
            {
                continue;
            }

            if (room->isTaskPossible() && room != currentRoom())
            {
                possibleRooms.push_back(room);
            }
        }
    }

    if (possibleRooms.size() == 0)
    {
        return;
    }

    std::shuffle(
        possibleRooms.begin(), possibleRooms.end(), std::default_random_engine(Randomizer::getRandomEngineSeed()));
    possibleRooms.at(0)->setTask(task);
}

std::optional<CRoom*> CMap::roomAt(const EDirections dir) const
{
    return roomAt(_playerPosition, dir);
}

std::optional<CRoom*> CMap::roomAt(const SRoomCoords& coords) const
{
    if (!coordsValid(coords))
    {
        return {};
    }

    return _map.at(coords.y).at(coords.x);
}

std::optional<CRoom*> CMap::roomAt(const SRoomCoords& coords, const EDirections dir) const
{
    SRoomCoords transposedCoords(coords);
    transposedCoords.transpose(dir);
    return roomAt(transposedCoords);
}

CMap::SRoomCoords CMap::getPlayerPosition() const
{
    return _playerPosition;
}
