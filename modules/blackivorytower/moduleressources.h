#pragma once

#include "moduleinfo.h"

#include <string>
#include <vector>

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
namespace BlackIvoryTower
{

static const unsigned int towerHeight = 25;

std::string moduleName();
Module::ModuleInfo moduleInfo();

std::string darkIvoryTower();

std::string lunatic();
std::string lunatics();

} // namespace BlackIvoryTower