#pragma once

#include <string>
#include <utility>
#include <vector>

#include "cgamestatetagnames.h"

namespace TagNames
{
namespace Cave
{
constexpr std::string_view cave = "Cave";
constexpr std::string_view isOpen = TagNames::Common::isOpen;
} // namespace Cave
} // namespace TagNames

class CRoom;
namespace CaveRessources
{
void initModule();
void deInitModule();
void initWorldMap(std::vector<CRoom*>& rooms);

std::string moduleName();
std::string dungeonEncounterName();

std::string questLog();

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

} // namespace CaveRessources
