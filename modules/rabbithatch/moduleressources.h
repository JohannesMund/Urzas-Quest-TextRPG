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
} // namespace RabbitHatch
} // namespace TagNames

class CRoom;
class CItem;
namespace RabbitHatch
{
Module::ModuleInfo moduleInfo();
std::string moduleName();

std::string katNothingH();
std::string rabbitHatchName();

} // namespace RabbitHatch
