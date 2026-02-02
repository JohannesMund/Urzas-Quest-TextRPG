#pragma once

#include <string>
#include <vector>

#include "module/moduleinfo.h"

namespace TagNames
{
namespace Shrine
{
constexpr std::string_view shrine = "Shrine";
constexpr std::string_view seenDuringPhase = "seenDuringPhase";
} // namespace Shrine
} // namespace TagNames

class CRoom;
namespace ShrineRessources
{
std::string moduleName();
} // namespace ShrineRessources

namespace ShrineInfo
{
Module::ModuleInfo moduleInfo();
}