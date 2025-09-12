#pragma once

#include <string>
#include <vector>

#include "cgamestatetagnames.h"

namespace TagNames
{
namespace BlackIvoryTower
{
constexpr std::string_view blackIvoryTower = "BlackIvoryTower";
constexpr std::string_view hadADoener = "HadADoener";
constexpr std::string_view isOpen = TagNames::Common::isOpen;
} // namespace BlackIvoryTower
} // namespace TagNames

class CRoom;
namespace BlackIvoryTowerRessources
{

static const unsigned int towerHeight = 25;

CRoom* roomFactory(const std::string_view& objectName);

void initModule();
void deInitModule();
void initWorldMap(std::vector<CRoom*>& rooms);
std::string questLog();

std::string darkIvoryTower();

std::string lunatic();
std::string lunatics();
std::string moduleName();
} // namespace BlackIvoryTowerRessources