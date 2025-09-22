#include "cweapon.h"
#include "cenemy.h"
#include "console.h"
#include "randomizer.h"

#include <format>

CWeapon::CWeapon(const Ressources::Items::EQuality quality) :
    CEquipment(Ressources::Items::EType::eWeapon, quality, TagNames::Item::Equipment::weapon)
{
    _hasBattleEffect = true;
    _hasBattleBuff = true;
}

void CWeapon::battleEffect(CEnemy* enemy)
{
    Console::printLn(std::format("You draw your {} at {} and try to look dangerous.", name(), enemy->name()));
}

void CWeapon::battleBuff(CEnemy* enemy, bool& endRound)
{
    if (doesEquipmentEffectFire())
    {
        Console::printLn(std::format("Your {} deals some extra damage", name()));
        enemy->dealDamage(extraDamage());
        endRound = true;
    }
}

std::string CWeapon::typeName() const
{
    return "Weapon";
}

CItem::ItemFilter CWeapon::equipmentTypeFilter() const
{
    return [](const CItem* item) -> bool { return dynamic_cast<const CWeapon*>(item) != nullptr; };
}

unsigned int CWeapon::extraDamage() const
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
