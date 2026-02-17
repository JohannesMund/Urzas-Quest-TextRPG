#pragma once

#include <string>
#include <vector>

#include "moduleinfo.h"

namespace TagNames
{
namespace Shrine
{
constexpr std::string_view shrine = "Shrine";
constexpr std::string_view seenDuringPhase = "seenDuringPhase";
} // namespace Shrine
} // namespace TagNames

namespace Shrine
{
std::string moduleName();
Module::ModuleInfo moduleInfo();
} // namespace Shrine
