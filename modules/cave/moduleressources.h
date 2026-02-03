#pragma once

#include "moduleinfo.h"
#include "ressources/jsontagnames.h"

#include <string>
#include <utility>
#include <vector>

namespace TagNames
{
namespace Cave
{
constexpr std::string_view cave = "Cave";
constexpr std::string_view caveBoss = "CaveBoss";
constexpr std::string_view openCave = "openCave";
constexpr std::string_view isOpen = TagNames::Common::isOpen;
} // namespace Cave
} // namespace TagNames

class CRoom;
class CTask;
namespace Cave
{

Module::ModuleInfo moduleInfo();
std::string moduleName();

std::string dungeonEncounterName();

static const unsigned int fightChance = 15;

std::string getRandomEnemyName();
std::string getRandomEnemyWeapon();

std::string getRandomDescription();

std::string getWellDescription(const int i);
std::string getWellQuestion(const int i);
std::string getWellEffect(const int i);

std::string getMapRoomDescription();

std::string getColoredBossString();
std::string getBossWeapon();

} // namespace Cave
