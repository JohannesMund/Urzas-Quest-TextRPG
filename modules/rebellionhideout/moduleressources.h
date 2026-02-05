#pragma once

#include "moduleinfo.h"

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
namespace RebellionHideout
{
Module::ModuleInfo moduleInfo();
std::string moduleName();
} // namespace RebellionHideout

namespace SandwichShop
{
Module::ModuleInfo moduleInfo();
std::string moduleName();

std::string sandwichShopName();
std::string mrSoop();

} // namespace SandwichShop
