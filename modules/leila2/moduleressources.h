#pragma once

#include "moduleinfo.h"

#include <string>

class CTask;
namespace TagNames
{
namespace Leila2
{
constexpr std::string_view goblinVillage = "goblinVillage";
constexpr std::string_view leilaCaptial = "leilaCapital";
constexpr std::string_view leila2Encounter = "leila2Encounter";
constexpr std::string_view leila2GoblinEncounter = "leilaGoblinEncounter";
} // namespace Leila2
} // namespace TagNames

namespace Leila2
{

Module::ModuleInfo moduleInfo();

std::string moduleName();
std::string encounterNameGuards();
std::string encounterNameFindRibbon();

std::string mork();
std::string gork();

std::string greenskin();
} // namespace Leila2
