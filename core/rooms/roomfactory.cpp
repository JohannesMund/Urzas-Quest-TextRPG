#include "roomfactory.h"
#include "cave/ccave.h"
#include "ccapital.h"
#include "cfield.h"
#include "cgamemanagement.h"
#include "cinjuredpet.h"
#include "croom.h"
#include "cstartingroom.h"
#include "ctown.h"

#include <nlohmann/json.hpp>

CRoom* RoomFactory::loadRoomFromSaveGame(const nlohmann::json& json)
{
    CRoom* newRoom = nullptr;
    if (CGameStateObject::compareObjectName(TagNames::Room::field, json))
    {
        newRoom = new CField();
    }
    if (CGameStateObject::compareObjectName(TagNames::Room::town, json))
    {
        newRoom = new CTown();
    }
    if (CGameStateObject::compareObjectName(TagNames::Room::capital, json))
    {
        newRoom = new CCapital();
    }
    if (CGameStateObject::compareObjectName(TagNames::Room::injuredPet, json))
    {
        newRoom = new CInjuredPet();
    }
    if (CGameStateObject::compareObjectName(TagNames::Room::startingRoom, json))
    {
        newRoom = new CStartingRoom();
    }

    if (newRoom != nullptr)
    {
        if (newRoom->load(json) == true)
        {
            return newRoom;
        }
        delete newRoom;
        return nullptr;
    }

    newRoom = CGameManagement::getInstance()->getProgressionInstance()->callModuleRoomFactory(
        CGameStateObject::getObjectNameFromJson(json));
    if (newRoom != nullptr)
    {
        if (newRoom->load(json) == true)
        {
            return newRoom;
        }
        delete newRoom;
    }
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
