#pragma once

#include <string>
#include <vector>

namespace TagNames
{
namespace FishingVille
{
constexpr std::string_view fishingVille = "FishingVille";
constexpr std::string_view buildEquipmentTask = "BuildEquipment";
constexpr std::string_view fishingVilleTask = "FishingVille";
constexpr std::string_view part = "Part";
constexpr std::string_view fishLevel = "FishLevel";
constexpr std::string_view boat = "Boat";
constexpr std::string_view boatPart = "BoatPart";
constexpr std::string_view fish = "Fish";
constexpr std::string_view fishingRod = "FishingRod";
constexpr std::string_view fishingRodPart = "FishingRodPart";

} // namespace FishingVille
} // namespace TagNames

class CRoom;
class CItem;
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

CRoom* roomFactory(const std::string_view& objectName);
CItem* itemFactory(const std::string_view& objectName);

std::string fishingVilleName();

std::string getFish(const EFishLevel level);
int getFishPrice(const EFishLevel level);
EFishLevel getRandomRarity(const unsigned int rodLevel, const unsigned int boatLevel);

} // namespace FishingVillageRessources
