#pragma once

#include <string>
#include <vector>

namespace Ressources
{

namespace Settings
{
constexpr unsigned int consoleWidth = 80;
constexpr std::string_view saveFileName = "savegame.json";
constexpr std::string_view logFileName = "log.txt";
constexpr std::string_view appName = "UruzsQuestTextRPG";
} // namespace Settings

namespace Config
{

constexpr bool superCowPowers = true;

constexpr unsigned int fieldWidth = 26;
constexpr unsigned int fieldHeight = 10;
constexpr unsigned int encounterChance = 10;
constexpr unsigned int fightChance = 15;

constexpr unsigned int numberOfTowns = 4;
constexpr unsigned int turnsUntilShopRefresh = 100;
constexpr int informationCost = 1000;

constexpr int maxHp = 10;
constexpr int maxHpMin = 3;
constexpr unsigned int gold = 100;
constexpr unsigned int initiative = 5;

} // namespace Config

namespace Game
{

std::string urza();
std::string whoTheFuckIsUrza();
std::string urzaWhoTheFuckIsUrza();

std::string princessLeila();
std::string leila();
std::string leilasRibbon();

std::string piefke();
std::string schniefke();
std::string bimmel();
std::string bommel();
std::string horst();

std::string fiego();
std::string brock();

std::string bimmelchen();
std::string pimmelchen();

std::string fishingFritz();
std::string dancingBard();

std::string mobi();
std::string darkMobi();

std::string kingJesster();

} // namespace Game

namespace Rooms
{
std::string getRandomDescription();
std::pair<std::string, std::string> getRandomTown();
std::pair<std::string, std::string> getCapital();
std::string getCapitalRejection();

std::string getRandomRumor();
} // namespace Rooms

namespace Items
{

enum class EType
{
    eWeapon,
    eShield,
    eArmor,
    eOther
};

enum class EQuality
{
    eJunk,
    eFair,
    eGood,
    eAwesomne
};

std::string sock();
std::string otherSock();

std::pair<std::vector<std::string>, std::string> getRandomEquipmentNamesAndDescription(const EType type,
                                                                                       const EQuality quality);

std::pair<std::string, std::string> getRandomJunkItems();

} // namespace Items

namespace Enemies
{
std::string getRandomEnemyName();
std::string getRandomEnemyWeapon();

std::pair<std::string, std::string> getRandomBountyName();

} // namespace Enemies

namespace Companion
{
enum class ECompanionType
{
    eAttacker,
    eDefender,
    eHealer,
    eScaryMonster
};

ECompanionType getRandomCompanionType();

constexpr unsigned int companionLevelCap = 5;
std::string nameForCompanionType(const ECompanionType& tp, const unsigned int level);
std::string typeAsString(const ECompanionType& tp);
} // namespace Companion

} // namespace Ressources
