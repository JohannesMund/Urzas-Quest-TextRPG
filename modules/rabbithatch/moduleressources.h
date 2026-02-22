#pragma once

#include "moduleinfo.h"

#include <string>
#include <vector>

namespace TagNames
{
namespace RabbitHatch
{
constexpr std::string_view rabbitHatch = "RabbitHatch";
constexpr std::string_view kat = "KatNothingH";
constexpr std::string_view apple = "Apple";
constexpr std::string_view rabbitFood = "RabbitFood";
constexpr std::string_view rabbit = "Rabbit";
constexpr std::string_view slasher = "Slasher";
} // namespace RabbitHatch
} // namespace TagNames

class CRoom;
class CItem;

namespace TagNames
{
namespace RabbitHatch
{
constexpr std::string_view appleEncounter = "AppleTree";
}
} // namespace TagNames

namespace RabbitHatch
{
Module::ModuleInfo moduleInfo();

std::string makeRabbitName();

std::string moduleName();

std::string katNothingH();
std::string rabbitHatchName();
std::string apple();
std::string katsBoots();
std::string coolAndStrong();
std::string slasher();
int rabbitRoastPrice();

} // namespace RabbitHatch
