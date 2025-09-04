#include "cguardstuff.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "randomizer.h"

#include <format>

CGuardStuff::CGuardStuff()
{
    std::vector<EPart> possibleStuff;
    possibleStuff.push_back(EPart::eUnknown);
    for (auto i : CGuardStuff::partIterator())
    {
        if (i != EPart::eUnknown && !has(i))
        {
            possibleStuff.push_back(i);
        }
    }

    _part = Randomizer::getRandomEntry<EPart>(possibleStuff);
    _name = nameForPart(_part);
    if (_part == EPart::eUnknown)
    {
        _description = "A totally random item related to guards and stuff. Just Random Guard Stuff";
    }
    else
    {
        _description = std::format(
            "A highly appreciated and well-known symbol of guard-ship. No guard is a real guard without his {}",
            nameForPart(_part));
    }

    _value = 200 + Randomizer::getRandom(500);
    _isSellable = true;
    _isBuyable = false;
}

CGuardStuff::EPart CGuardStuff::part() const
{
    return _part;
}

CItem::ItemFilter CGuardStuff::guardStuffFilter(const EPart part)
{
    return [part](const CItem* item)
    {
        auto p = dynamic_cast<const CGuardStuff*>(item);
        if (p != nullptr)
        {
            return p->part() == part;
        }
        return false;
    };
}

std::string CGuardStuff::nameForPart(const EPart part)
{
    switch (part)
    {
    case EPart::eUnknown:
    default:
        return std::format("totally random {}Guard {}stuff{}", CC::fgBlue(), CC::fgYellow(), CC::ccReset());
        break;
    case EPart::eBatch:
        return std::format("{}Guard's {}Batch{}", CC::fgBlue(), CC::fgYellow(), CC::ccReset());
        break;
    case EPart::eSword:
        return std::format("{}Guard's {}Sword{}", CC::fgBlue(), CC::fgYellow(), CC::ccReset());
        break;
    case EPart::eSash:
        return std::format("{}Guard's {}Sash{}", CC::fgBlue(), CC::fgYellow(), CC::ccReset());
        break;
    case EPart::eHelmet:
        return std::format("{}Guard's {}Helmet{}", CC::fgBlue(), CC::fgYellow(), CC::ccReset());
        break;
    case EPart::eBoot:
        return std::format("{}Guard's {}Boot{}", CC::fgBlue(), CC::fgYellow(), CC::ccReset());
        break;
    case EPart::eFirstAidKit:
        return std::format("{}Guard's {}First-Aid Kit{}", CC::fgBlue(), CC::fgYellow(), CC::ccReset());
        break;

    }
}

bool CGuardStuff::has(const EPart part)
{
    return CGameManagement::getInventoryInstance()->hasItem(guardStuffFilter(part));
}

bool CGuardStuff::hasAll()
{
    for (auto i : CGuardStuff::partIterator())
    {
        if (!has(i))
        {
            return false;
        }
    }
    return true;
}

std::vector<std::string> CGuardStuff::listMissingParts()
{
    std::vector<std::string> missingStuff;
    for (auto i : CGuardStuff::partIterator())
    {
        if (!has(i))
        {

            missingStuff.push_back(nameForPart(i));
        }
    }
    return missingStuff;
}
