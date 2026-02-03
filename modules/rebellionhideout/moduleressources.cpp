#include "moduleressources.h"
#include "colorize.h"
#include "rebellionhideout/cbagofingredients.h"
#include "rebellionhideout/csandwichshop.h"

#include <format>

Module::ModuleInfo SandwichShop::moduleInfo()
{
    const auto roomFactory = [](const std::string_view& objectName) -> CRoom*
    {
        if (TagNames::RebellionHideout::rebellionHideout.compare(objectName) == 0)
        {
            return new CSandwichShop();
        }
        return nullptr;
    };

    const auto itemFactory = [](const std::string_view& objectName) -> CItem*
    {
        if (TagNames::RebellionHideout::bagOfIngredients.compare(objectName) == 0)
        {
            return new CBagOfIngredients();
        }
        return nullptr;
    };

    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = moduleName();
    moduleInfo.translatorFile = "rebellionhideout";
    moduleInfo.gameStage = Module::EGameStage::eProvenAsHero,

    moduleInfo.questLogFunction = []() { return "Own a sandwich shop"; };

    moduleInfo.roomFactory = roomFactory;
    moduleInfo.itemFactory = itemFactory;
    moduleInfo.initWorldMapFunction = [](std::vector<CRoom*>& rooms) { rooms.push_back(new CSandwichShop()); };

    return moduleInfo;
}

Module::ModuleInfo RebellionHideout::moduleInfo()
{
    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = moduleName();
    moduleInfo.translatorFile = "rebellionhideout";
    moduleInfo.gameStage = Module::EGameStage::eLearnedAboutCult,

    moduleInfo.questLogFunction = []() { return "Find the rebellion hideout"; };

    return moduleInfo;
}

std::string SandwichShop::moduleName()
{
    return "SandwichShop";
}

std::string SandwichShop::sandwichShopName()
{
    return std::format("{}<-SOOP{}WAY->{}", CC::fgLightYellow(), CC::fgGreen(), CC::ccReset());
}

std::string SandwichShop::mrSoop()
{
    return std::format("{}Mr. {}Soop{}", CC::fgGreen(), CC::fgLightYellow(), CC::ccReset());
}

std::string RebellionHideout::moduleName()
{
    return "RebellionHideout";
}
