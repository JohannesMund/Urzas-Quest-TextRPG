#pragma once

#include <string>

namespace TagNames
{
namespace Leila2
{
constexpr std::string_view goblinVillage = "goblinVillage";
constexpr std::string_view leilaCaptial = "leilaCapital";
} // namespace Leila2
} // namespace TagNames

namespace Leila2Ressources
{
void initModule();
void deInitModule();

std::string moduleName();
std::string encounterNameGuards();
std::string encounterNameFindRibbon();

std::string questLog();

std::string mork();
std::string gork();

std::string greenskin();
} // namespace Leila2Ressources
