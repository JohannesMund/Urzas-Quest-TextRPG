#include "csword.h"
#include "cenemy.h"
#include "console.h"
#include "randomizer.h"

#include <format>

CSword::CSword(const Ressources::Items::EQuality quality) : CEquipment(Ressources::Items::EType::eSword, quality)
{
    _hasBattleEffect = true;
    _hasBattleBuff = true;
}

void CSword::battleEffect(CEnemy* enemy)
{
    Console::printLn(std::format("You draw your {} at {} and try to look dangerous.", _name, enemy->name()));
}

void CSword::battleBuff(CEnemy* enemy, bool& endRound)
{
    if (doesEquipmentEffectFire())
    {
        Console::printLn(std::format("Your {} deals some extra damage", _name));
        enemy->dealDamage(extraDamage());
        endRound = true;
    }
}

std::string CSword::typeName() const
{
    return "Sword";
}

std::function<bool(const CItem*)> CSword::equipmentTypeFilter() const
{
    return [](const CItem* item) -> bool { return dynamic_cast<const CSword*>(item) != nullptr; };
}

unsigned int CSword::extraDamage() const
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
