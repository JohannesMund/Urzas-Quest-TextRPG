#include "moduleressources.h"
#include "colorize.h"
#include "rebellionhideout/csandwichshop.h"

#include <format>

void RebellionHideoutRessources::initModule()
{
}

void RebellionHideoutRessources::deInitModule()
{
}

void RebellionHideoutRessources::initWorldMap(std::vector<CRoom*>& rooms)
{
    rooms.push_back(new CSandwichShop());
}

std::string RebellionHideoutRessources::moduleName()
{
    return "Rebellion Hideout";
}

std::string RebellionHideoutRessources::questLog()
{
    return "Find the Hideout of the Rebellion";
}

std::string RebellionHideoutRessources::sandwichShopName()
{
    return std::format("{}<-SOOP{}WAY->{}", CC::fgLightYellow(), CC::fgGreen(), CC::ccReset());
}

std::string RebellionHideoutRessources::mrSoop()
{
    return std::format("{}Mr. {}Soop{}", CC::fgGreen(), CC::fgLightYellow(), CC::ccReset());
}
