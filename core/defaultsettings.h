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