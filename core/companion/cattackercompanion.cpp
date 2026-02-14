#include "cattackercompanion.h"
#include "cenemy.h"
#include "console.h"
#include "ressources.h"

#include <format>

CAttackerCompanion::CAttackerCompanion() : CCompanion(TagNames::Companion::attackCompanion)
{
}

std::string CAttackerCompanion::name() const
{
    return CC::colorizeString(
        Ressources::Companion::nameForCompanionType(Ressources::Companion::ECompanionType::eAttacker, _level),
        CC::fgRed(),
        CC::fgLightRed());
}

std::string CAttackerCompanion::type() const
{
    return Ressources::Companion::typeAsString(Ressources::Companion::ECompanionType::eAttacker);
}

void CAttackerCompanion::preBattle(CEnemy*)
{
    if (_level <= 0)
    {
        return;
    }
    Console::printLn(std::format("{} tries to look dangerous but it does not work. At least it is cute", name()));
}

void CAttackerCompanion::battleAction(CEnemy* enemy, bool&)
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

void CAttackerCompanion::postBattle(CEnemy*)
{
    if (_level <= 0)
    {
        return;
    }
    Console::printLn(std::format("{} looks victorious.", name()));
}

int CAttackerCompanion::shield(const int i)
{
    return i;
}

std::string CAttackerCompanion::translatorModuleName() const
{
    return std::string();
}
