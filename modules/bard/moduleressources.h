#pragma once

#include <string>

#include "moduleinfo.h"

namespace TagNames
{
constexpr std::string_view dancingBard = "DancingBard";
}
namespace Bard
{
std::string moduleName();
std::string encounterName();

Module::ModuleInfo moduleInfo();
} // namespace Bard
