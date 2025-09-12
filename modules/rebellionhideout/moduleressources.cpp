#include "moduleressources.h"
#include "colorize.h"
#include "rebellionhideout/csandwichshop.h"

#include <format>

void RebellionHideoutRessources::initModuleSandwichShop()
{
}

void RebellionHideoutRessources::deInitModuleSandwichShop()
{
}

void RebellionHideoutRessources::initModuleRebellionHideout()
{
}

void RebellionHideoutRessources::deInitModuleRebellionHideout()
{
}

std::string RebellionHideoutRessources::questLogRebellionHideout()
{
    return "Find the rebellion hideout";
}

std::string RebellionHideoutRessources::questLogSandwichShop()
{
    return "Own a sandwich shop";
}

void RebellionHideoutRessources::initWorldMap(std::vector<CRoom*>& rooms)
{
    rooms.push_back(new CSandwichShop());
}

CRoom* RebellionHideoutRessources::roomFactory(const std::string_view& objectName)
{
    if (TagNames::RebellionHideout::rebellionHideout.compare(objectName) == 0)
    {
        return new CSandwichShop();
    }
    return nullptr;
}

std::string RebellionHideoutRessources::moduleNameSandwichShop()
{
    return "SandwichShop";
}

std::string RebellionHideoutRessources::sandwichShopName()
{
    return std::format("{}<-SOOP{}WAY->{}", CC::fgLightYellow(), CC::fgGreen(), CC::ccReset());
}

std::string RebellionHideoutRessources::mrSoop()
{
    return std::format("{}Mr. {}Soop{}", CC::fgGreen(), CC::fgLightYellow(), CC::ccReset());
}

std::string RebellionHideoutRessources::moduleNameRebellionHideout()
{
    return "RebellionHideout";
}
