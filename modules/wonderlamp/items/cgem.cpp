#include "cgem.h"
#include "wonderlamp/moduleressources.h"

CGem::CGem() : CItem(TagNames::WonderLamp::gem)
{
    _isSellable = true;
    _isBuyable = false;
    _value = 500;

    _name = WonderLamp::getRandomGem();
    _description = tr("A beautiful {}, looks like the ones on your {}", _name, WonderLamp::wonderlamp());
}

CItem::ItemFilter CGem::gemFilter()
{
    return [](const CItem* item) { return dynamic_cast<const CGem*>(item) != nullptr; };
}

std::string CGem::translatorModuleName() const
{
    return std::string(WonderLamp::moduleName());
}
