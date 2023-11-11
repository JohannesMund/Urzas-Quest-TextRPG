#include "cequipment.h"
#include "console.h"
#include "randomizer.h"

#include <format>
CEquipment::CEquipment() : CItem()
{
    _name = "";
}

bool CEquipment::isEnhancable() const
{
    return _level < _levelCap;
}

std::string CEquipment::name() const
{
    if (_namesByLevel.size() == 0)
    {
        return "something";
    }

    if (_level > _namesByLevel.size())
    {
        return _namesByLevel.at(_namesByLevel.size() - 1);
    }
    return _namesByLevel.at(_level);
}

unsigned int CEquipment::level() const
{
    return _level;
}

unsigned int CEquipment::upgradeCost() const
{
    unsigned int upgradeModifier = 0;

    switch (_quality)
    {
    case EQuality::eJunk:
    default:
        upgradeModifier = 2;
        break;
    case EQuality::eFair:
        upgradeModifier = 3;
        break;
    case EQuality::eGood:
        upgradeModifier = 5;
        break;
    case EQuality::eAwesomne:
        upgradeModifier = 10;
        break;
    }

    return 150 + (_level * 150 * _level * upgradeModifier);
}

void CEquipment::enhance()
{
    if (!isEnhancable())
    {
        return;
    }

    _level++;
    Console::printLn(
        std::format("your {} has been upgraded to to a {}", _namesByLevel.at(_level - 1), _namesByLevel.at(_level)));
}

std::function<bool(const CItem*)> CEquipment::equipmentFilter()
{
    return [](const CItem* item) -> bool { return CEquipment::isEquipment(item); };
}

bool CEquipment::isEquipment(const CItem* item)
{
    return dynamic_cast<const CEquipment*>(item) != nullptr;
}

std::function<bool(const CItem*)> CEquipment::enhancableEquipmentFilter()
{
    return [](const CItem* item) -> bool
    {
        auto equipment = dynamic_cast<const CEquipment*>(item);
        if (equipment == nullptr)
        {
            return false;
        }
        return equipment->isEnhancable();
    };
}

std::function<CEquipment*(CItem*)> CEquipment::equipmentTransformation()
{
    return [](CItem* item) -> CEquipment* { return dynamic_cast<CEquipment*>(item); };
}

bool CEquipment::doesEquipmentEffectFire() const
{
    return Randomizer::getRandom(100) <= _level * 10;
}
