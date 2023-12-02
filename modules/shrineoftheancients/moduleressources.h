#pragma once

#include <string>
#include <vector>

class CRoom;
namespace ShrineRessources
{

void initModule();
void deInitModule();
void initWorldMap(std::vector<CRoom*>& rooms);

std::string moduleName();
std::string questLog();

} // namespace ShrineRessources