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

static const unsigned int rodLevelCap = 5;
static const unsigned int boatLevelCap = 5;

static const int necessaryRodParts = 3;
static const int necessaryBoatParts = 7;

std::string moduleNameMakeRod();
std::string moduleNameMakeBoat();
std::string moduleNameFishLegend();

std::string questLogMakeRod();
std::string questLogMAkeBoat();
std::string questLogFishLegend();

void initModuleMakeRod();
void initModuleMakeBoat();
void initModuleFishLegend();

void deInitModuleMakeRod();
void deInitModuleMakeBoat();
void deInitModuleFishLegend();

void initWorldMap(std::vector<CRoom*>& rooms);

std::string fishingVilleName();

std::string getFish(const EFishLevel level);
unsigned int getFishPrice(const EFishLevel level);
EFishLevel getRandomRarity(const unsigned int rodLevel, const unsigned int boatLevel);

} // namespace FishingVillageRessources
