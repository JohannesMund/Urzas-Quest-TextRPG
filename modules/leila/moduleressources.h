#pragma once

#include <string>

class CTask;
namespace TagNames
{
namespace Leila
{
constexpr std::string_view leila = "LeilaTask";
constexpr std::string_view leilaTown = "LeilaTownTask";

} // namespace Leila
} // namespace TagNames

namespace LeilaRessources
{
void initModule();
void deInitModule();
CTask* taskFactory(const std::string_view& objectName);

std::string moduleName();
std::string questLog();

} // namespace LeilaRessources
