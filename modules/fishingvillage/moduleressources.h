#pragma once

#include <string>
#include <vector>

class CRoom;
namespace FishingVillageRessources
{
enum class EFishLevel
{
    eCommon,
    eUncommon,
    eRare,
    eUltraRare,
    eLegend
};

std::string moduleName();

void initModule();
void deInitModule();
void initWorldMap(std::vector<CRoom*>& rooms);

std::string fishingVilleName();
std::string fishingFritz();

std::string getFish(const EFishLevel level);

} // namespace FishingVillageRessources
