#include "moduleressources.h"
#include "colorconsole.h"

#include <format>
std::string BardRessources::moduleName()
{
    return "DancingBard";
}

std::string BardRessources::encounterName()
{
    return std::format("{}Dan{}cing {}Bard{}", CC::fgRed(), CC::fgLightRed(), CC::fgGreen(), CC::ccReset());
}
