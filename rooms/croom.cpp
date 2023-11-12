#include <iostream>

#include "cgamemanagement.h"
#include "console.h"
#include "croom.h"
#include "ctask.h"
#include "ressources.h"

CRoom::CRoom()
{
    _description = Ressources::Rooms::getRandomDescription();
    _encounterPossible = true;
}

CRoom::~CRoom()
{
}

void CRoom::execute()
{
    Console::printLn(_description);
    Console::br();

    if (hasTask())
    {
        _task->execute();
        if (_task->isFinished())
        {
            delete _task;
            _task = nullptr;
            _showInFogOfWar = false;
        }
    }
    _seen = true;
}

void CRoom::setTask(CTask* task)
{
    _task = task;
    _showInFogOfWar = true;
}

CTask* CRoom::takeTask()
{
    auto task = _task;
    _task = nullptr;
    return task;
}

bool CRoom::isTaskPossible() const
{
    return _taskPossible && !hasTask();
}

bool CRoom::hasTask() const
{
    return _task != nullptr;
}

bool CRoom::isSpecialRoom() const
{
    return false;
}

bool CRoom::isEmptyRoom() const
{
    return false;
}

void CRoom::blockPath(const CMap::EDirections dir, const bool block)
{
    switch (dir)
    {
    case CMap::EDirections::eNorth:
        _pathNorth = !block;
        break;
    case CMap::EDirections::eEast:
        _pathEast = !block;
        break;
    case CMap::EDirections::eSouth:
        _pathSouth = !block;
        break;
    case CMap::EDirections::eWest:
        _pathWest = !block;
        break;
    default:
        break;
    }
}

bool CRoom::north() const
{
    return _pathNorth;
}

bool CRoom::east() const
{
    return _pathEast;
}

bool CRoom::south() const
{
    return _pathSouth;
}

bool CRoom::west() const
{
    return _pathWest;
}

bool CRoom::seen() const
{
    return _seen;
}

void CRoom::setSeen(const bool b)
{
    _seen = b;
}

bool CRoom::showInFogOfWar() const
{
    return _showInFogOfWar;
}

std::string CRoom::mapSymbol() const
{
    if (hasTask())
    {
        return "!";
    }
    return " ";
}