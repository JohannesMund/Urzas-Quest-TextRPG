#pragma once

#include <string>
#include <vector>

namespace Ressources
{

namespace Settings
{
static const unsigned int consoleWidth = 80;
} // namespace Settings

namespace Config
{

static const bool superCowPowers = true;

static const unsigned int fieldWidth = 26;
static const unsigned int fieldHeight = 10;
static const unsigned int encounterChance = 10;
static const unsigned int fightChance = 15;

static const unsigned int numberOfTowns = 4;
static const unsigned int turnsUntilShopRefresh = 100;
static const int informationCost = 1000;

static const int maxHp = 10;
static const int maxHpMin = 3;
static const unsigned int gold = 100;
static const unsigned int initiative = 5;

} // namespace Config

namespace Game
{

std::string urza();
std::string whoTheFuckIsUrza();
std::string urzaWhoTheFuckIsUrza();

std::string princessLayla();
std::string layla();
std::string laylasRibbon();

std::string fiego();
std::string brock();

std::string bimmelchen();
std::string pimmelchen();

std::string fishingFritz();
std::string dancingBard();

std::string mobi();

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

static const unsigned int companionLevelCap = 5;
std::string nameForCompanionType(const ECompanionType& tp, const unsigned int level);
std::string typeAsString(const ECompanionType& tp);
} // namespace Companion

} // namespace Ressources
