#pragma once

#include "moduleinfo.h"

#include <string>
#include <utility>

class CTask;
class CItem;
namespace TagNames
{
namespace RatFarm
{
constexpr std::string_view ratFarm = ("RatFarm");
constexpr std::string_view turnip = ("Turnip");
constexpr std::string_view size = TagNames::Common::size;
} // namespace RatFarm
} // namespace TagNames

namespace RatFarm
{

std::string moduleName();
Module::ModuleInfo moduleInfo();

const unsigned int ratCount = 15;

std::string getTurnip();
std::string getCarrot();

std::string getColoredBossString();

namespace TurnipFactory
{
void addTurnips(unsigned int cnt);
}
} // namespace RatFarm
