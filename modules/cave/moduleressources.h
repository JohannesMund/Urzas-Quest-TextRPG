#pragma once

#include <string>
#include <utility>

namespace CaveRessources
{

void initModule();
void deInitModule();

std::string moduleName();

static const unsigned int fightChance = 15;

std::string getRandomEnemyName();
std::string getRandomEnemyWeapon();

std::string getEncounterName();
std::string getRandomDescription();

std::string getWellDescription(const int i);
std::string getWellQuestion(const int i);
std::string getWellEffect(const int i);

std::string getMapRoomDescription();

std::string getColoredBossString();
std::string getBossWeapon();

} // namespace CaveRessources
