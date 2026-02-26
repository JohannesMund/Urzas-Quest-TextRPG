#pragma once

#include "moduleinfo.h"

#include <string>
#include <vector>

namespace TagNames
{
namespace WonderLamp
{
constexpr std::string_view wonderlamp = "Wonderlamp";
constexpr std::string_view djinn = "Djinn";
constexpr std::string_view genie = "Genie";
constexpr std::string_view jeannie = "Jeannie";

} // namespace WonderLamp
} // namespace TagNames

class CRoom;
class CItem;

namespace WonderLamp
{
Module::ModuleInfo moduleInfo();
std::string moduleName();

std::string djinn();
std::string jeannie();
std::string genie();
std::string wonderlamp();

} // namespace WonderLamp
