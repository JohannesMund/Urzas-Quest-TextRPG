#include "moduleressources.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "cratfarmencounter.h"
#include "cratfarmturnip.h"
#include "randomizer.h"

#include <format>

std::string RatFarmRessources::getTurnip()
{
    return std::format("{}turnip{}", CC::fgLightGray(), CC::ccReset());
}

std::string RatFarmRessources::getCarrot()
{
    return std::format("{}carrot{}", CC::fgLightRed(), CC::ccReset());
}

void RatFarmRessources::TurnipFactory::addTurnips(unsigned int cnt)
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

std::string RatFarmRessources::moduleName()
{
    return "RatFarm";
}

void RatFarmRessources::initModule()
{
    CGameManagement::getInstance()->registerEncounter(new CRatFarmEncounter());
}

void RatFarmRessources::deInitModule()
{
    CGameManagement::getInstance()->unregisterEncounterByModuleName(moduleName());
}

std::string RatFarmRessources::getColoredBossString()
{
    return std::format("{0}Go{1}d-M{2}ot{1}he{2}r o{0}f a{1}ll {0}Ra{2}ts{3}",
                       CC::fgYellow(),
                       CC::fgLightRed(),
                       CC::fgLightYellow(),
                       CC::ccReset());
}

std::string RatFarmRessources::questLog()
{
    return std::format("Clear lady {}s {} farm from the rats.", getCarrot(), getTurnip());
}
