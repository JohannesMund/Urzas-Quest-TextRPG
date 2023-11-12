#pragma once

#include <string>
#include <vector>

namespace Ressources
{

std::string urza();
std::string whoTheFuckIsUrza();
std::string urzaWhoTheFuckIsUrza();

namespace Settings
{
static const unsigned int consoleWidth = 80;
} // namespace Settings

namespace Config
{

unsigned int getXpForLevel(const unsigned int level);

static const unsigned int fieldWidth = 10;
static const unsigned int fieldHeight = 10;
static const unsigned int encounterChance = 10;
static const unsigned int fightChance = 15;

static const unsigned int numberOfTowns = 3;

static const unsigned int maxHp = 10;
static const unsigned int maxHpMin = 3;
static const unsigned int gold = 100;
static const unsigned int initiative = 5;

} // namespace Config

namespace Game
{
namespace ShrineRessources
{
std::string moduleName();
}
} // namespace Game

namespace Rooms
{
std::string getRandomDescription();
std::pair<std::string, std::string> getRandomTown();
std::string getRandomRumor();
} // namespace Rooms

namespace Items
{

std::string sock();
std::string otherSock();

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
