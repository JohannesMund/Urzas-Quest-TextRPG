#include <vector>
namespace Settings
{
constexpr unsigned int consoleWidth = 80;
constexpr std::string_view saveFileName = "savegame.json";
constexpr std::string_view settingsFileName = "settings.json";
constexpr std::string_view logFileName = "log.txt";
constexpr std::string_view appName = "UruzsQuestTextRPG";
const std::vector<std::string_view> supportedLanguages = {"en", "de"};
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

constexpr std::string_view currentLanguage = "en";

} // namespace Config