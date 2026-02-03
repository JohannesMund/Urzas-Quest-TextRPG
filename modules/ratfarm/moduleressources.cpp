#include "moduleressources.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "cratfarmencounter.h"
#include "cratfarmtask.h"
#include "cratfarmturnip.h"
#include "ctask.h"
#include "randomizer.h"

#include <format>

std::string RatFarm::getTurnip()
{
    return std::format("{}turnip{}", CC::fgLightGray(), CC::ccReset());
}

std::string RatFarm::getCarrot()
{
    return std::format("{}carrot{}", CC::fgLightRed(), CC::ccReset());
}

void RatFarm::TurnipFactory::addTurnips(unsigned int cnt)
{
    for (auto i = 0U; i <= cnt; i++)
    {
        auto sz = Randomizer::getRandom(10);
        if (sz >= 9)
        {
            CGameManagement::getInventoryInstance()->addItem(new CRatFarmTurnip(CRatFarmTurnip::TurnipSize::L));
        }
        else if (sz > 5)
        {
            CGameManagement::getInventoryInstance()->addItem(new CRatFarmTurnip(CRatFarmTurnip::TurnipSize::M));
        }
        else
        {
            CGameManagement::getInventoryInstance()->addItem(new CRatFarmTurnip(CRatFarmTurnip::TurnipSize::S));
        }
    }
}

std::string RatFarm::moduleName()
{
    return "RatFarm";
}

std::string RatFarm::getColoredBossString()
{
    return std::format("{0}Go{1}d-M{2}ot{1}he{2}r o{0}f a{1}ll {0}Ra{2}ts{3}",
                       CC::fgYellow(),
                       CC::fgLightRed(),
                       CC::fgLightYellow(),
                       CC::ccReset());
}

Module::ModuleInfo RatFarm::moduleInfo()
{
    const auto taskFactory = [](const std::string_view& objectName) -> CTask*
    {
        if (TagNames::RatFarm::ratFarm.compare(objectName) == 0)
        {
            return new CRatFarmTask();
        }
        return nullptr;
    };

    const auto itemFactory = [](const std::string_view& objectName) -> CItem*
    {
        if (TagNames::RatFarm::ratFarm.compare(objectName) == 0)
        {
            return new CRatFarmTurnip();
        }
        return nullptr;
    };

    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = moduleName();
    moduleInfo.translatorFile = "ratfarm";
    moduleInfo.gameStage = Module::EGameStage::eSeenBard,

    moduleInfo.initFunction = []() { CGameManagement::getInstance()->registerEncounter(new CRatFarmEncounter()); };
    moduleInfo.deInitFunction = []() { CGameManagement::getInstance()->unregisterEncounterByModuleName(moduleName()); };
    moduleInfo.questLogFunction = []()
    { return std::format("Clear lady {}s {} farm from the rats.", getCarrot(), getTurnip()); };

    moduleInfo.taskFactory = taskFactory;
    moduleInfo.itemFactory = itemFactory;

    return moduleInfo;
}
