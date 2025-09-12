#pragma once

#include <nlohmann/json_fwd.hpp>

class CRoom;
class CCave;
class CTown;
class CCapital;
class CInjuredPet;

namespace RoomFactory
{
CRoom* loadRoomFromSaveGame(const nlohmann::json& json);

CRoom* makeRoom();
CTown* makeTown();
CCapital* makeCapital();
CInjuredPet* makeInjuredPet();
} // namespace RoomFactory
