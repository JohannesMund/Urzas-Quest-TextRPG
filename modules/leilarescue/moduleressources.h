#pragma once

#include "moduleinfo.h"

#include <string>

class CSupportCompanion;
class CTask;
class CItem;
namespace TagNames
{
namespace LeilaRescue
{
constexpr std::string_view leilaCompanion = "LeilaCompanion";
constexpr std::string_view guardCompanion = "GuardCompanion";
constexpr std::string_view findGuards = "FindGuards";
constexpr std::string_view guardStuff = "GuardStuff";
constexpr std::string_view leilaRescueCapital = "LeilaRescueCapital";
constexpr std::string_view dungeonBoss = "DungeonBoss";
constexpr std::string_view mafiaMoney = "MafiaMoney";
constexpr std::string_view findGuardsStep = "FindGuardStep";
constexpr std::string_view stuffCollectionStarted = "StuffCollectionStarted";
constexpr std::string_view lootItemGeneratorRegistered = "LootItemGeneratorRegistered";
constexpr std::string_view part = TagNames::Item::part;

} // namespace LeilaRescue
} // namespace TagNames

namespace LeilaRescue
{
std::string moduleName();
Module::ModuleInfo moduleInfo();

void questAccepted();

std::string questText();

std::string getColoredBossString();
std::string getBossWeapon();

} // namespace LeilaRescue
