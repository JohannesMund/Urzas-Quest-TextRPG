#pragma once

class CRoom;
class CCave;
class CTown;
class CInjuredPet;
class CShrineOfTheAncients;
namespace RoomFactory
{

CRoom* makeRoom();
CTown* makeTown();
CCave* makeCave();
CShrineOfTheAncients* makeShrine();
CInjuredPet* makeInjuredPet();

} // namespace RoomFactory
