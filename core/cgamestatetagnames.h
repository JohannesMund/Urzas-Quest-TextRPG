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
constexpr std::string_view gold = "gold";
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
} // namespace TagNames
