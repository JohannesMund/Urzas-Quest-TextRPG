#pragma once

#include <string>
#include <vector>

class CRoom;
namespace RebellionHideoutRessources
{

void initModule();
void deInitModule();
void initWorldMap(std::vector<CRoom*>& rooms);

std::string moduleName();

std::string questLog();

std::string sandwichShopName();
std::string mrSoop();

} // namespace RebellionHideoutRessources
