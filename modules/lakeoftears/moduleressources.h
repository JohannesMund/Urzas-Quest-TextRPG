#pragma once

#include <string>

namespace TagNames
{
namespace LakeOfTears
{
constexpr std::string_view lakeOfTears = "lakeOfTears";
constexpr std::string_view lakeOfTearsBoss = "lakeOfTearsBoss";
} // namespace LakeOfTears
} // namespace TagNames

namespace LakeTearsRessources
{
void initModule();
void deInitModule();

std::string moduleName();
std::string questLog();

std::string getColoredsBossString();

} // namespace LakeTearsRessources
