#pragma once

#include <string>
#include <vector>

class CRoom;
namespace BlackIvoryTowerRessources
{

static const unsigned int towerHeight = 25;

void initModule();
void deInitModule();
void initWorldMap(std::vector<CRoom*>& rooms);
std::string questLog();

std::string darkIvoryTower();

std::string lunatic();
std::string lunatics();
std::string moduleName();
} // namespace BlackIvoryTowerRessources