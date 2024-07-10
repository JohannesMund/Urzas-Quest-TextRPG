#include "cguardcompanion.h"
#include "../moduleressources.h"
#include "cenemy.h"
#include "console.h"
#include "randomizer.h"

#include <format>

CGuardCompanion::CGuardCompanion(const std::string_view& name) : CSupportCompanion(LeilaRescueRessources::moduleName())
{
    if (Randomizer::getRandom(1))
    {
        _type = Ressources::Companion::ECompanionType::eAttacker;
    }
    else
    {
        _type = Ressources::Companion::ECompanionType::eDefender;
    }
    _level = Randomizer::getRandom(3) + 2;
    _name = name;
}

std::string CGuardCompanion::name() const
{
    return _name;
}

std::string CGuardCompanion::type() const
{
    return Ressources::Companion::typeAsString(_type);
}

void CGuardCompanion::preBattle(CEnemy* enemy)
{
    Console::printLn(std::format("{} stays at your side in your battle against {}.", name(), enemy->name()));
}

void CGuardCompanion::battleAction(CEnemy* enemy, bool&)
{
    if (_level <= 0 || _type != Ressources::Companion::ECompanionType::eAttacker)
    {
        return;
    }
    if (fireDefaultAction())
    {
        Console::printLn(std::format("{} attacks the enemy and deals 1 damage.", name()));
        enemy->dealDamage(1);
    }
    else
    {
        Console::printLn(std::format("{} holds his weapon and looks dangerous.", name()));
    }
}

void CGuardCompanion::postBattle(CEnemy* enemy)
{
    Console::printLn(std::format("{} taunts the defeated {}.", name(), enemy->name()));
}

int CGuardCompanion::shield(const int i)
{
    if (_level <= 0 || _type != Ressources::Companion::ECompanionType::eDefender)
    {
        return i;
    }
    if (fireDefaultAction())
    {
        Console::printLn(std::format("{} raises his shield to protect you.", name()));
        return i - 1;
    }

    return i;
}
