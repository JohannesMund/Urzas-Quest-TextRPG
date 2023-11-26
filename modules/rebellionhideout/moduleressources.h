#pragma once

#include <string>
#include <vector>

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
