#include "cfishingrodpart.h"
#include "colorconsole.h"
#include "randomizer.h"

#include <format>

CFishingRodPart::CFishingRodPart()
{
    switch (Randomizer::getRandom(3))
    {
    case 0:
    default:

        _part = EPart::eRod;
        _name = nameForPart(_part);
        _description = "A long, straight, elastic stick. perfect for building a fishing rod";
        break;
    case 1:

        _part = EPart::eThread;
        _name = nameForPart(_part);

        _description = "A very long, very strong thread. This will make an awesomne fishing line.";
        break;
    case 2:
        _part = EPart::eHook;
        _name = nameForPart(_part);
        _description = "Some wire. with a little work, this will be your fishing hook";
        break;
    };

    _value = 10;
    _isSellable = true;
    _isBuyable = false;
}

CFishingRodPart::EPart CFishingRodPart::part() const
{
    return _part;
}

CItem::ItemFilter CFishingRodPart::partFilter(const EPart part)
{
    return [part](const CItem* item)
    {
        auto p = dynamic_cast<const CFishingRodPart*>(item);
        if (p != nullptr)
        {
            return p->part() == part;
        }
        return false;
    };
}

std::string CFishingRodPart::nameForPart(const EPart part)
{
    switch (part)
    {
    case EPart::eRod:
    default:
        return std::format("{}Straight Stick{}", CC::fgYellow(), CC::ccReset());
    case EPart::eThread:
        return std::format("{}Long Thread{}", CC::fgLightGray(), CC::ccReset());
    case EPart::eHook:
        return std::format("{}Wire{}", CC::fgLightCyan(), CC::ccReset());
    }
}
