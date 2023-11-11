#include "moduleressources.h"
#include "cgamemanagement.h"
#include "colorconsole.h"
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
    for (int i = 0; i <= cnt; i++)
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
