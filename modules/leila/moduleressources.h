#pragma once

#include "moduleinfo.h"

#include <string>

class CTask;
namespace TagNames
{
namespace Leila
{
constexpr std::string_view leila = "LeilaTask";
constexpr std::string_view leilaTown = "LeilaTownTask";

} // namespace Leila
} // namespace TagNames

namespace Leila
{
std::string moduleName();
Module::ModuleInfo moduleInfo();
} // namespace Leila
