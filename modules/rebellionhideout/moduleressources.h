#pragma once

#include "cgamestatetagnames.h"

#include <string>
#include <vector>

namespace TagNames
{
namespace RebellionHideout
{
constexpr std::string_view rebellionHideout = "rebellionHideout";
constexpr std::string_view gold = TagNames::Common::gold;
constexpr std::string_view turns = TagNames::Common::turns;
constexpr std::string_view playerOwnsShot = "playerOwnsShop";
constexpr std::string_view playerDiscoveredHideout = "playerDiscoveredHideout";
constexpr std::string_view sandwiches = "sandwiches";
constexpr std::string_view ingredientStore = "ingredientStore";
constexpr std::string_view ingredient = "ingredient";
constexpr std::string_view count = TagNames::Common::count;
} // namespace RebellionHideout
} // namespace TagNames

class CRoom;
namespace RebellionHideoutRessources
{

void initModuleSandwichShop();
void initModuleRebellionHideout();

void deInitModuleSandwichShop();
void deInitModuleRebellionHideout();

void initWorldMap(std::vector<CRoom*>& rooms);

std::string moduleNameSandwichShop();
std::string moduleNameRebellionHideout();

std::string questLogSandwichShop();
std::string questLogRebellionHideout();

std::string sandwichShopName();
std::string mrSoop();

} // namespace RebellionHideoutRessources
