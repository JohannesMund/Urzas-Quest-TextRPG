#include "carmor.h"
#include "cenemy.h"
#include "console.h"
#include "randomizer.h"
#include "ressources.h"

#include <format>

CArmor::CArmor(const Ressources::Items::EQuality quality) : CEquipment(Ressources::Items::EType::eArmor, quality)
{
    _hasBattleEffect = true;
    _hasShieldingAction = true;
}

void CArmor::battleEffect(CEnemy* enemy)
{
    Console::printLn(std::format(
        "You feel confident, that your {} will protect you from the furious attacks of {}", _name, enemy->name()));
}

int CArmor::shield(const unsigned int i)
{
    int shieldAmount = Randomizer::getRandom(_level + 1);
    if (shieldAmount == 0)
    {
        return i;
    }

    if (Randomizer::getRandom(100) <= _level * 10)
    {
        Console::printLn(std::format("Your armor absorbs {} damage", shieldAmount));
        return std::max(i - shieldAmount, 0U);
    }

    return i;
}

std::string CArmor::typeName() const
{
    return "Armor";
}

std::function<bool(const CItem*)> CArmor::equipmentTypeFilter() const
{
    return [](const CItem* item) -> bool { return dynamic_cast<const CArmor*>(item) != nullptr; };
}

unsigned int CArmor::shieldAmount() const
{
    switch (_quality)
    {
    case Ressources::Items::EQuality::eJunk:
    default:
        return 1;
    case Ressources::Items::EQuality::eFair:
        return Randomizer::getRandom(2) + 1;
    case Ressources::Items::EQuality::eGood:
        return Randomizer::getRandom(3) + 1;
    case Ressources::Items::EQuality::eAwesomne:
        return Randomizer::getRandom(5) + 1;
    }
    return 0;
}
