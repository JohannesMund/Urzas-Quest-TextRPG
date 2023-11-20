#pragma once

#include <string>
#include <utility>
#include <vector>

class CRoom;
namespace CaveRessources
{

void initModule();
void deInitModule();
void initWorldMap(std::vector<CRoom*>& rooms);

std::string moduleName();
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
