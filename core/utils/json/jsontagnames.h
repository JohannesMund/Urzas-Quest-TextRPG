#pragma once
#include <string>

namespace TagNames
{
namespace Translator
{
constexpr std::string_view translation = "Translations";
constexpr std::string_view core = "Core";
constexpr std::string_view source = "Source";
} // namespace Translator

namespace Common
{
constexpr std::string_view objectName = "ObjectName";
constexpr std::string_view moduleName = "ModuleName";
constexpr std::string_view name = "Name";
constexpr std::string_view description = "Description";
constexpr std::string_view level = "Level";
constexpr std::string_view x = "Coord-X";
constexpr std::string_view y = "Coord-Y";
constexpr std::string_view isOpen = "IsOpen";
constexpr std::string_view gold = "Gold";
constexpr std::string_view turns = "Turns";
constexpr std::string_view count = "Count";
constexpr std::string_view size = "Size";
} // namespace Common

namespace FileSpec
{
constexpr std::string_view fileSpec = "FileSpec";
constexpr std::string_view version = "Version";
constexpr std::string_view dateTime = "DateTime";
constexpr std::string_view fileType = "FileType";

constexpr std::string_view typeSave = "SaveGame";
constexpr std::string_view typeSettings = "Settings";
constexpr std::string_view typeTranslation = "Translation";

constexpr std::string_view name = TagNames::Common::name;
} // namespace FileSpec

namespace GameSettings
{
constexpr std::string_view gameSettings = "GameSettings";

constexpr std::string_view superCowPowers = "SuperCow";

constexpr std::string_view fieldWidth = "FieldWidth";
constexpr std::string_view fieldHeight = "FieldHeight";
constexpr std::string_view encounterChance = "EncounterChance";
constexpr std::string_view fightChance = "FightChance";

constexpr std::string_view numberOfTowns = "NumberOfTowns";
constexpr std::string_view turnsUntilShopRefresh = "TurnsUntilShowRefresh";
constexpr std::string_view informationCost = "InformationCost";

constexpr std::string_view maxHp = "MaxHp";
constexpr std::string_view maxHpMin = "MaxHpMin";
constexpr std::string_view gold = "Gold";
constexpr std::string_view initiative = "Initiative";

constexpr std::string_view currentLanguage = "CurrentLanguage";

} // namespace GameSettings

namespace Progression
{
constexpr std::string_view progression = "Progression";
constexpr std::string_view currentStage = "CurrentStage";
constexpr std::string_view turns = TagNames::Common::turns;
constexpr std::string_view bodyCount = "BodyCount";
constexpr std::string_view genocideCount = "GenocideCount";
constexpr std::string_view finishedModules = "FinishedModules";
} // namespace Progression

namespace Player
{
constexpr std::string_view player = "Player";
constexpr std::string_view hp = "Hp";
constexpr std::string_view maxHp = "MaxHp";
constexpr std::string_view gold = TagNames::Common::gold;
constexpr std::string_view xp = "Pp";
constexpr std::string_view initiative = "Initiative";
constexpr std::string_view supporters = "Supporters";
constexpr std::string_view name = TagNames::Common::name;
constexpr std::string_view level = TagNames::Common::level;
} // namespace Player

namespace Companion
{
constexpr std::string_view companion = "Companion";
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
constexpr std::string_view playerPosition = "PlayerPosition";
constexpr std::string_view roomMatrix = "RoomMatrix";
} // namespace Map

namespace Room
{
constexpr std::string_view room = "Room";
constexpr std::string_view field = "Field";
constexpr std::string_view town = "Town";
constexpr std::string_view capital = "Capital";
constexpr std::string_view injuredPet = "InjuredPet";
constexpr std::string_view startingRoom = "StartingRoom";
constexpr std::string_view pathNorth = "PathNorth";
constexpr std::string_view pathEast = "PathEast";
constexpr std::string_view pathSouth = "PathSouth";
constexpr std::string_view pathWest = "PathWest";
constexpr std::string_view showInFogOfWar = "ShowInFogOfWar";
constexpr std::string_view seen = "Seen";
constexpr std::string_view description = TagNames::Common::description;
constexpr std::string_view name = TagNames::Common::name;
constexpr std::string_view isOpen = TagNames::Common::isOpen;
constexpr std::string_view petIsDead = "PetIsDead";
} // namespace Room

namespace Task
{
constexpr std::string_view task = "Task";
constexpr std::string_view bountyHunt = "BountyHunt";
constexpr std::string_view finished = "Finished";
constexpr std::string_view autoExecute = "AutoExecute";
constexpr std::string_view reward = "Reward";
constexpr std::string_view name = TagNames::Common::name;
} // namespace Task

namespace Item
{
constexpr std::string_view item = "Item";
namespace Equipment
{
constexpr std::string_view armor = "Armor";
constexpr std::string_view equipment = "Equipment";
constexpr std::string_view shield = "Shield";
constexpr std::string_view weapon = "Weapon";
} // namespace Equipment
namespace Story
{
constexpr std::string_view laylasRibbon = "LaylasRibbon";
constexpr std::string_view shaggysSandwich = "ShaggysSandwich";
constexpr std::string_view urzasGlasses = "UrzasGlasses";

} // namespace Story
constexpr std::string_view inventory = "Inventory";
constexpr std::string_view bomb = "Bomb";
constexpr std::string_view healingPotion = "HealingPotion";
constexpr std::string_view heartContainer = "HeartContainer";
constexpr std::string_view junkItem = "JunkItem";
constexpr std::string_view phoenixFeather = "PhoenixFeather";
constexpr std::string_view sandwich = "Sandwich";
constexpr std::string_view part = "Part";
} // namespace Item

} // namespace TagNames
