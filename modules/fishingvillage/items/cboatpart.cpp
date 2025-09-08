#include "cboatpart.h"
#include "colorize.h"
#include "randomizer.h"

#include <format>

CBoatPart::CBoatPart() : CJunkItem("CBoatPart")
{
    switch (Randomizer::getRandom(3))
    {
    case 0:
    default:

        _part = EPart::eBoard;
        _name = nameForPart(_part);
        _description = "A long, straight, board.";
        break;
    case 1:

        _part = EPart::eNail;
        _name = nameForPart(_part);

        _description = "A nail, made to fix a board to another board.";
        break;
    case 2:
        _part = EPart::eRope;
        _name = nameForPart(_part);
        _description = "Rope, stong and sturdy.";
        break;
    };

    _value = 25;
    _isSellable = true;
    _isBuyable = false;
}

CBoatPart::EPart CBoatPart::part() const
{
    return _part;
}

CItem::ItemFilter CBoatPart::partFilter(const EPart part)
{
    return [part](const CItem* item)
    {
        auto p = dynamic_cast<const CBoatPart*>(item);
        if (p != nullptr)
        {
            return p->part() == part;
        }
        return false;
    };
}

std::string CBoatPart::nameForPart(const EPart part)
{
    switch (part)
    {
    case EPart::eBoard:
    default:
        return std::format("{}Wooden Board{}", CC::fgYellow(), CC::ccReset());
    case EPart::eNail:
        return std::format("{}Nail{}", CC::fgCyan(), CC::ccReset());
    case EPart::eRope:
        return std::format("{}Rope{}", CC::fgLightYellow(), CC::ccReset());
    }
}

nlohmann::json CBoatPart::save() const
{
    nlohmann::json o = CItem::save();
    o["part"] = _part;
    return o;
}
