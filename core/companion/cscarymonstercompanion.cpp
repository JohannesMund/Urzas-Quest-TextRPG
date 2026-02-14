#include "cscarymonstercompanion.h"
#include "cenemy.h"
#include "console.h"

#include <format>

CScaryMonsterCompanion::CScaryMonsterCompanion() : CCompanion("CScaryMonsterCompanion")
{
}

std::string CScaryMonsterCompanion::name() const
{
    return CC::colorizeString(
        Ressources::Companion::nameForCompanionType(Ressources::Companion::ECompanionType::eScaryMonster, _level),
        CC::fgYellow(),
        CC::fgLightYellow());
}

std::string CScaryMonsterCompanion::type() const
{
    return Ressources::Companion::typeAsString(Ressources::Companion::ECompanionType::eScaryMonster);
}

void CScaryMonsterCompanion::preBattle(CEnemy* enemy)
{
    if (_level <= 0)
    {
        return;
    }
    if (fireDefaultAction())
    {
        Console::printLn(std::format("{} scares {} so much, that it hurts itself.", name(), enemy->name()));
        enemy->dealDamage(1);
    }
    else
    {
        Console::printLn(std::format("{} tries to look dangerous but it does not work. At least it is cute", name()));
    }
}

void CScaryMonsterCompanion::battleAction(CEnemy* enemy, bool&)
{
    if (_level <= 0)
    {
        return;
    }

    if (fireDefaultAction())
    {
        Console::printLn(std::format("Your {} attacks the enemy and deals 1 damage.", name()));
        enemy->dealDamage(1);
    }
    else
    {
        Console::printLn(std::format("Your {} jumps around the enemy and plans it's next attack.", name()));
    }
}

void CScaryMonsterCompanion::postBattle(CEnemy*)
{
    if (_level <= 0)
    {
        return;
    }

    if (_level > 0)
    {
        Console::printLn(std::format("{} looks victorious.", name()));
    }
}

int CScaryMonsterCompanion::shield(const int i)
{
    return i;
}

std::string_view CScaryMonsterCompanion::translatorModuleName() const
{
    return std::string_view();
}
