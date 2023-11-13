#pragma once

#include <string>

namespace SewerRessources
{

void initModule();
void deInitModule();

std::string moduleName();
std::string encounterName();

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

} // namespace SewerRessources
