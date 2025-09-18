#pragma once

#include <string>

class CSupportCompanion;
class CTask;
namespace TagNames
{
namespace LeilaRescue
{
constexpr std::string_view leilaCompanion = "leilaCompanion";
constexpr std::string_view guardCompanion = "guardCompanion";
constexpr std::string_view findGuards = "findGuards";
constexpr std::string_view leilaRescueCapital = "leilaRescueCapital";
constexpr std::string_view dungeonBoss = "dungeonBoss";
constexpr std::string_view mafiaMoney = "mafiaMoney";
constexpr std::string_view findGuardsStep = "findGuardStep";
constexpr std::string_view stuffCollectionStarted = "stuffCollectionStarted";
constexpr std::string_view lootItemGeneratorRegistered = "lootItemGeneratorRegistered";

} // namespace LeilaRescue
} // namespace TagNames

namespace LeilaRescueRessources
{
void initModule();
void deInitModule();

void questAccepted();

CTask* taskFactory(const std::string_view& objectName);

CSupportCompanion* companionFactory(const std::string_view& name);

std::string moduleName();
std::string questLog();

std::string questText();

std::string getColoredBossString();
std::string getBossWeapon();

} // namespace LeilaRescueRessources
