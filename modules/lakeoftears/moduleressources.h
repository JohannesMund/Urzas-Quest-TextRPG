#pragma once

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

namespace LakeTearsRessources
{
void initModule();
void deInitModule();
CTask* taskFactory(const std::string_view& objectName);

std::string moduleName();
std::string questLog();

std::string getColoredsBossString();

} // namespace LakeTearsRessources
