#pragma once

#include "moduleinfo.h"

#include <string>

class CTask;
namespace TagNames
{
namespace Leila
{
constexpr std::string_view leila = "LeilaTask";
constexpr std::string_view leilaEncounter = "LeilaEncounter";
constexpr std::string_view leilaTown = "LeilaTownTask";
constexpr std::string_view tatooParlor = "TatooParlor";

} // namespace Leila
} // namespace TagNames

namespace Leila
{
std::string moduleName();
Module::ModuleInfo moduleInfo();

std::string inky();
std::string inkystattooParlor();

} // namespace Leila
