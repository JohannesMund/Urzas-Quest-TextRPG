#pragma once
#include <string>

namespace TagNames
{
namespace Common
{
constexpr std::string_view objectName = "objectName";
constexpr std::string_view moduleName = "moduleName";
constexpr std::string_view name = "name";
constexpr std::string_view description = "description";
constexpr std::string_view level = "level";
constexpr std::string_view x = "coord-x";
constexpr std::string_view y = "coord-y";
constexpr std::string_view isOpen = "isOpen";
constexpr std::string_view gold = "gold";
constexpr std::string_view turns = "turns";
constexpr std::string_view count = "count";
} // namespace Common

namespace FileSpec
{
constexpr std::string_view fileSpec = "fileSpec";
constexpr std::string_view version = "version";
constexpr std::string_view name = TagNames::Common::name;
} // namespace FileSpec

namespace Player
{
constexpr std::string_view player = "Player";
constexpr std::string_view hp = "hp";
constexpr std::string_view maxHp = "maxHp";
constexpr std::string_view gold = TagNames::Common::gold;
constexpr std::string_view xp = "xp";
constexpr std::string_view initiative = "initiative";
constexpr std::string_view supporters = "supporters";
constexpr std::string_view name = TagNames::Common::name;
constexpr std::string_view level = TagNames::Common::level;
} // namespace Player

namespace Companion
{
constexpr std::string_view attackCompanion = "AttackCompanion";
constexpr std::string_view defenderCompanion = "DefenderCompanion";
constexpr std::string_view healerCompanion = "HealerCompanion";
constexpr std::string_view scaryMonsterCompanion = "ScaryMonsterCompanion";
constexpr std::string_view name = TagNames::Common::name;
constexpr std::string_view description = TagNames::Common::description;
constexpr std::string_view level = TagNames::Common::level;
} // namespace Companion

namespace Map
{
constexpr std::string_view map = "Map";
constexpr std::string_view playerPosition = "playerPosition";
constexpr std::string_view roomMatrix = "roomMatrix";
} // namespace Map

namespace Room
{
constexpr std::string_view field = "Field";
constexpr std::string_view town = "Town";
constexpr std::string_view capital = "Capital";
constexpr std::string_view injuredPet = "InjuredPet";
constexpr std::string_view startingRoom = "startingRoom";

constexpr std::string_view pathNorth = "pathNorth";
constexpr std::string_view pathEast = "pathEast";
constexpr std::string_view pathSouth = "pathSouth";
constexpr std::string_view pathWest = "pathWest";
constexpr std::string_view showInFogOfWar = "showInFogOfWar";
constexpr std::string_view seen = "seen";
constexpr std::string_view description = TagNames::Common::description;
constexpr std::string_view name = TagNames::Common::name;
constexpr std::string_view isOpen = TagNames::Common::isOpen;
constexpr std::string_view petIsDead = "petIsDead";
} // namespace Room

namespace Task
{
constexpr std::string_view task = "Task";
constexpr std::string_view bountyHunt = "BountyHunt";

constexpr std::string_view finished = "finished";
constexpr std::string_view autoExecute = "autoExecute";
constexpr std::string_view reward = "reward";
constexpr std::string_view name = TagNames::Common::name;

} // namespace Task

} // namespace TagNames
