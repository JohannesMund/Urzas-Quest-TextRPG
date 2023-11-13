#include "cequipment.h"
#include "console.h"
#include "randomizer.h"

#include <format>
CEquipment::CEquipment(const Ressources::Items::EType type, const Ressources::Items::EQuality quality) : CItem()
{
    _level = 1;

    _type = type;
    _quality = quality;
    switch (quality)
    {
    case Ressources::Items::EQuality::eJunk:
    default:
        _levelCap = 3;
        break;
    case Ressources::Items::EQuality::eFair:
        _levelCap = 4;
        break;
    case Ressources::Items::EQuality::eGood:
        _levelCap = 5;
        break;
    case Ressources::Items::EQuality::eAwesomne:
        _levelCap = 9;
        break;
    }

    auto namesAndDescription = Ressources::Items::getRandomEquipmentNamesAndDescription(type, quality);

    _namesByLevel = namesAndDescription.first;
    _description = namesAndDescription.second;
}

bool CEquipment::isEnhancable() const
{
    return _level < _levelCap;
}

std::string CEquipment::name() const
{
    return nameByLevel(_level);
}

unsigned int CEquipment::value() const
{
    return 150 * qualityModifier() * ((qualityModifier() - 1) * 2);
}

unsigned int CEquipment::level() const
{
    return _level;
}

unsigned int CEquipment::upgradeCost() const
{

    return 150 + (_level * 150 * _level * (qualityModifier() + 1));
}

void CEquipment::enhance()
{
    if (!isEnhancable())
    {
        return;
    }

    _level++;
    Console::printLn(std::format("your {} has been upgraded to to a {}", nameByLevel(_level), nameByLevel(_level + 1)));
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

unsigned int CEquipment::qualityModifier() const
{
    switch (_quality)
    {
    case Ressources::Items::EQuality::eJunk:
    default:
        return 1;
        break;
    case Ressources::Items::EQuality::eFair:
        return 3;
        break;
    case Ressources::Items::EQuality::eGood:
        return 5;
        break;
    case Ressources::Items::EQuality::eAwesomne:
        return 10;
        break;
    }
}

std::string CEquipment::nameByLevel(const unsigned int level) const
{
    if (_namesByLevel.size() == 0)
    {
        return "something";
    }

    if (level > _namesByLevel.size())
    {
        return _namesByLevel.at(_namesByLevel.size());
    }
    return _namesByLevel.at(level);
}
