#pragma once

class CRoom;
class CCave;
class CTown;
class CCapital;
class CInjuredPet;

namespace RoomFactory
{

CRoom* makeRoom();
CTown* makeTown();
CCapital* makeCapital();
CInjuredPet* makeInjuredPet();

} // namespace RoomFactory
