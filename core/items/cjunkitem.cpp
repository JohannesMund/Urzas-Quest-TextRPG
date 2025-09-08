#include "cjunkitem.h"
#include "randomizer.h"
#include "ressources.h"

CJunkItem::CJunkItem(const std::string& objectName) : CItem(objectName)
{
    auto it = Ressources::Items::getRandomJunkItems();
    _name = it.first;
    _description = it.second;

    _isSellable = true;
    _value = Randomizer::getRandom(50) + 25;
}

CItem::ItemFilter CJunkItem::junkItemFilter()
{
    return [](const CItem* item) -> bool { return dynamic_cast<const CJunkItem*>(item) != nullptr; };
}
