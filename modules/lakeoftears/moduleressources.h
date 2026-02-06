#pragma once

#include "moduleinfo.h"

#include <string>

class CTask;
namespace TagNames
{
namespace LakeOfTears
{
constexpr std::string_view lakeOfTears = "lakeOfTears";
constexpr std::string_view lakeOfTearsBoss = "lakeOfTearsBoss";
constexpr std::string_view steps = "steps";
} // namespace LakeOfTears
} // namespace TagNames

namespace LakeOfTears
{
Module::ModuleInfo moduleInfo();
std::string moduleName();

std::string getColoredsBossString();
} // namespace LakeOfTears
