#include "crabbithatchfood.h"
#include "colorize.h"
#include "crabbithatchapple.h"
#include "rabbithatch/moduleressources.h"

CRabbithatchFood::CRabbithatchFood() : CItem(TagNames::RabbitHatch::rabbitFood)
{
    _name = tr("{}Rabbit{} food{}", CC::fgLightGreen(), CC::fgGreen(), CC::ccReset());
    _description = tr("A Bag full of greens. Grass, a lot of clover (is there a four leaved one?) some herbs. A nice "
                      "collection of food. well not for you, obviously, but any rabbit will love it.");
}

std::string CRabbithatchFood::translatorModuleName() const
{
    return std::string(RabbitHatch::moduleName());
}

CItem::ItemFilter CRabbithatchFood::fishFilter()
{
    return [](const CItem* item) { return dynamic_cast<const CRabbithatchFood*>(item) != nullptr; };
}