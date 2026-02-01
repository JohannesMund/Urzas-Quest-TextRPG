#include "roomfactory.h"
#include "cave/ccave.h"
#include "ccapital.h"
#include "cfield.h"
#include "cgamemanagement.h"
#include "cinjuredpet.h"
#include "console.h"
#include "croom.h"
#include "cstartingroom.h"
#include "ctown.h"
#include "save/exceptions.h"

#include <iostream>
#include <nlohmann/json.hpp>

CRoom* RoomFactory::loadRoomFromSaveGame(const nlohmann::json& json)
{
    CRoom* newRoom = nullptr;

    if (CGameStateObject::compareObjectName(TagNames::Room::field, json))
    {
        newRoom = new CField();
    }
    else if (CGameStateObject::compareObjectName(TagNames::Room::town, json))
    {
        newRoom = new CTown();
    }
    else if (CGameStateObject::compareObjectName(TagNames::Room::capital, json))
    {
        newRoom = new CCapital();
    }
    else if (CGameStateObject::compareObjectName(TagNames::Room::injuredPet, json))
    {
        newRoom = new CInjuredPet();
    }
    else if (CGameStateObject::compareObjectName(TagNames::Room::startingRoom, json))
    {
        newRoom = new CStartingRoom();
    }
    else
    {
        newRoom = CGameManagement::getInstance()->getProgressionInstance()->callModuleRoomFactory(
            CGameStateObject::getObjectNameFromJson(json));
    }

    if (newRoom != nullptr)
    {
        try
        {
            newRoom->load(json);
            return newRoom;
        }
        catch (const SaveFile::CSaveFileException& e)
        {
            Console::printErr("Load room error", e.what());
            delete newRoom;
            return nullptr;
        }
    }
    throw SaveFile::CSaveFileException(std::format("Unknown Room: {}", CGameStateObject::getObjectNameFromJson(json)));
    return nullptr;
}

CRoom* RoomFactory::makeRoom()
{
    return new CField();
}

CTown* RoomFactory::makeTown()
{
    return new CTown();
}

CInjuredPet* RoomFactory::makeInjuredPet()
{
    return new CInjuredPet();
}

CCapital* RoomFactory::makeCapital()
{
    return new CCapital();
}
