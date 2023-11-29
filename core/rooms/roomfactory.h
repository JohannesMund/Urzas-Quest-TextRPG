#pragma once

class CRoom;
class CCave;
class CTown;
class CCapital;
class CInjuredPet;
class CShrineOfTheAncients;
namespace RoomFactory
{

CRoom* makeRoom();
CTown* makeTown();
CCapital* makeCapital();
CShrineOfTheAncients* makeShrine();
CInjuredPet* makeInjuredPet();

} // namespace RoomFactory
