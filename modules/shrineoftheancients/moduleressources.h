#pragma once

#include <string>
#include <vector>

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

void initModule();
void deInitModule();
void initWorldMap(std::vector<CRoom*>& rooms);

std::string moduleName();
std::string questLog();

} // namespace ShrineRessources