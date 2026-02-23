#include "crabbitfood.h"
#include "capple.h"
#include "colorize.h"
#include "rabbitfarm/moduleressources.h"

CRabbitFood::CRabbitFood() : CItem(TagNames::RabbitFarm::rabbitFood)
{
    _name = tr("{}Rabbit{} food{}", CC::fgLightGreen(), CC::fgGreen(), CC::ccReset());
    _description = tr("A Bag full of greens. Grass, a lot of clover (is there a four leaved one?) some herbs. A nice "
                      "collection of food. well not for you, obviously, but any rabbit will love it.");

    _isConsumable = false;
    _isUsableFromInventory = false;
    _isUsableFromBattle = false;
    _isSellable = false;
}

std::string CRabbitFood::translatorModuleName() const
{
    return std::string(RabbitFarm::moduleName());
}

CItem::ItemFilter CRabbitFood::rabbitFoodFilter()
{
    return [](const CItem* item) { return dynamic_cast<const CRabbitFood*>(item) != nullptr; };
}