#pragma once

#include <string>

namespace TagNames
{
namespace Leila
{
constexpr std::string_view leila = "LeilaTask";
constexpr std::string_view leilaTown = "LeilaTownTask";

} // namespace Leila
} // namespace TagNames

namespace LeilaRessources
{
void initModule();
void deInitModule();

std::string moduleName();
std::string questLog();

} // namespace LeilaRessources
