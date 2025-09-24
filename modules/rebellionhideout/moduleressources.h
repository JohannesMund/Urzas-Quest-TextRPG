#pragma once

#include "save/jsontagnames.h"

#include <string>
#include <vector>

namespace TagNames
{
namespace RebellionHideout
{
constexpr std::string_view rebellionHideout = "RebellionHideout";
constexpr std::string_view bagOfIngredients = "BagOfIngredients";
constexpr std::string_view gold = TagNames::Common::gold;
constexpr std::string_view turns = TagNames::Common::turns;
constexpr std::string_view playerOwnsShot = "PlayerOwnsShop";
constexpr std::string_view playerDiscoveredHideout = "PlayerDiscoveredHideout";
constexpr std::string_view sandwiches = "Sandwiches";
constexpr std::string_view ingredientStore = "IngredientStore";
constexpr std::string_view ingredient = "Ingredient";
constexpr std::string_view itemGeneratorsRegistered = "ItemGeneratorsRegistered";
constexpr std::string_view count = TagNames::Common::count;
} // namespace RebellionHideout
} // namespace TagNames

class CRoom;
class CItem;
namespace RebellionHideoutRessources
{

void initModuleSandwichShop();
void initModuleRebellionHideout();

void deInitModuleSandwichShop();
void deInitModuleRebellionHideout();

void initWorldMap(std::vector<CRoom*>& rooms);

CRoom* roomFactory(const std::string_view& objectName);
CItem* itemFactory(const std::string_view& objectName);

std::string moduleNameSandwichShop();
std::string moduleNameRebellionHideout();

std::string questLogSandwichShop();
std::string questLogRebellionHideout();

std::string sandwichShopName();
std::string mrSoop();

} // namespace RebellionHideoutRessources
