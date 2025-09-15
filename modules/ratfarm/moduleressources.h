#pragma once

#include <string>
#include <utility>

class CTask;
namespace TagNames
{
namespace RatFarm
{
constexpr std::string_view ratFarm = ("ratFarm");
constexpr std::string_view turnip = ("turnip");
} // namespace RatFarm
} // namespace TagNames

namespace RatFarmRessources
{

void initModule();
void deInitModule();

CTask* taskFactory(const std::string_view& objectName);

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
