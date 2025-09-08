#include "cshield.h"
#include "cenemy.h"
#include "console.h"
#include "randomizer.h"

#include <format>

CShield::CShield(const Ressources::Items::EQuality quality) :
    CEquipment(Ressources::Items::EType::eShield, quality, "CShield")
{
    _hasBattleEffect = true;
    _hasBattleBuff = true;
}

void CShield::battleEffect(CEnemy*)
{
    Console::printLn(std::format("You raise your {} to protect you.", name()));
}

void CShield::battleBuff(CEnemy* enemy, bool& endRound)
{
    if (doesEquipmentEffectFire())
    {
        Console::printLn(std::format("Your {} reflects some damage from the enemy attack", name()));
        enemy->dealDamage(shieldDamage());
        endRound = true;
    }
}

std::string CShield::typeName() const
{
    return "Shield";
}

CItem::ItemFilter CShield::equipmentTypeFilter() const
{
    return [](const CItem* item) -> bool { return dynamic_cast<const CShield*>(item) != nullptr; };
}

unsigned int CShield::shieldDamage() const
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
