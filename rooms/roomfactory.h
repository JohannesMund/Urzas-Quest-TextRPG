#pragma once

class CRoom;
class CCave;
class CTown;
class CInjuredPet;
namespace RoomFactory
{

CRoom* makeRoom();
CTown* makeTown();
CCave* makeCave();
CInjuredPet* makeInjuredPet();

} // namespace RoomFactory
