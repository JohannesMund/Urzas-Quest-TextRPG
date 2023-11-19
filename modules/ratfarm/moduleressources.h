#pragma once

#include <string>
#include <utility>

namespace RatFarmRessources
{

void initModule();
void deInitModule();

std::string moduleName();
std::string questLog();

const unsigned int ratCount = 15;

std::string getTurnip();
std::string getCarrot();

std::string getColoredBossString();

namespace TurnipFactory
{
void addTurnips(unsigned int cnt);
}
} // namespace RatFarmRessources
