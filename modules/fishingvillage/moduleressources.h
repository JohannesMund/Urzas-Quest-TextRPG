#pragma once

#include "moduleinfo.h"

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
namespace FishingVillage
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

std::string fishingVilleName();

std::string getFish(const EFishLevel level);
int getFishPrice(const EFishLevel level);
EFishLevel getRandomRarity(const unsigned int rodLevel, const unsigned int boatLevel);

} // namespace FishingVillage

namespace FishingVillageMakeRod
{
std::string moduleName();
Module::ModuleInfo moduleInfo();
} // namespace FishingVillageMakeRod

namespace FishingVillageMakeBoat
{
std::string moduleName();
Module::ModuleInfo moduleInfo();
} // namespace FishingVillageMakeBoat

namespace FishingVillageFishLegend
{
std::string moduleName();
Module::ModuleInfo moduleInfo();
} // namespace FishingVillageFishLegend
