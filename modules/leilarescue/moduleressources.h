#pragma once

#include <string>

namespace LeilaRescueRessources
{
void initModule();
void deInitModule();

void questAccepted();

std::string moduleName();
std::string questLog();

std::string questText();

std::string getColoredBossString();
std::string getBossWeapon();

} // namespace LeilaRescueRessources
