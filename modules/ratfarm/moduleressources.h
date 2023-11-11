#pragma once

#include <string>
#include <utility>

namespace RatFarmRessources
{
std::string moduleName();

const unsigned int ratCount = 15;

std::string getTurnip();
std::string getCarrot();

namespace TurnipFactory
{
void addTurnips(unsigned int cnt);
}
} // namespace RatFarmRessources
