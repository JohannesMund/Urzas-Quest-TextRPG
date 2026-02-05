#pragma once
#include <string>

namespace TagNames
{
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
} // namespace TagNames
