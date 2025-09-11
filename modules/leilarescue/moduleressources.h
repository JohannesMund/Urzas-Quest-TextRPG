#pragma once

#include <string>

class CSupportCompanion;

namespace TagNames
{
namespace LeilaRescue
{
constexpr std::string_view LeilaCompanion = "CLeilaCompanion";
constexpr std::string_view GuardCompanion = "CGuardCompanion";
} // namespace LeilaRescue
} // namespace TagNames

namespace LeilaRescueRessources
{
void initModule();
void deInitModule();

void questAccepted();

CSupportCompanion* companionFactory(const std::string_view& name);

std::string moduleName();
std::string questLog();

std::string questText();

std::string getColoredBossString();
std::string getBossWeapon();

} // namespace LeilaRescueRessources
