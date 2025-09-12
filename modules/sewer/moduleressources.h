#pragma once

#include <string>

namespace TagNames
{
namespace Sewer
{
constexpr std::string_view sever = "sewer";
}
} // namespace TagNames

namespace SewerRessources
{

void initModule();
void deInitModule();

std::string moduleName();
std::string questLog();

std::string encounterName();
std::string dungeonEncounterName();

static const unsigned int fightChance = 15;

std::string getRandomEnemyName();
std::string getRandomEnemyWeapon();

std::string getRandomDescription();

std::string getWellDescription(const int i);
std::string getWellQuestion(const int i);
std::string getWellEffect(const int i);

std::string getMapRoomDescription();
std::string getBossRoomDescription();

std::string getColoredBossString();
std::string getBossWeapon();

std::string hotdog();

} // namespace SewerRessources
