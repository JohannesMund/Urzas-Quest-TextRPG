#pragma once

#include "moduleinfo.h"

#include <string>
#include <vector>

namespace TagNames
{
namespace RabbitFarm
{
constexpr std::string_view rabbitFarm = "RabbitFarm";
constexpr std::string_view rabbitHatch = "RabbitHatch";
constexpr std::string_view kat = "KatNottingH";
constexpr std::string_view apple = "Apple";
constexpr std::string_view rabbitFood = "RabbitFood";
constexpr std::string_view rabbit = "Rabbit";
constexpr std::string_view slasher = "Slasher";
} // namespace RabbitFarm
} // namespace TagNames

class CRoom;
class CItem;

namespace TagNames
{
namespace RabbitFarm
{
constexpr std::string_view appleEncounter = "AppleTree";
constexpr std::string_view rabbitClearingEncounter = "RabbitClearing";

} // namespace RabbitFarm
} // namespace TagNames

namespace RabbitFarm
{
Module::ModuleInfo moduleInfo();

std::string makeRabbitName();

std::string moduleName();

std::string katNottingH();
std::string rabbitHatchName();
std::string rabbitFarmName();
std::string apple();
std::string katsBoots();
std::string coolAndStrong();
std::string slasher();
int rabbitRoastPrice();

} // namespace RabbitFarm
