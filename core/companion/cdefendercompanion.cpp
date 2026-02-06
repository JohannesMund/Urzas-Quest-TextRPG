#include "cdefendercompanion.h"
#include "console.h"
#include "ressources.h"

#include <format>

CDefenderCompanion::CDefenderCompanion() : CCompanion(TagNames::Companion::defenderCompanion)
{
}

std::string CDefenderCompanion::name() const
{
    return CC::colorizeString(
        Ressources::Companion::nameForCompanionType(Ressources::Companion::ECompanionType::eDefender, _level),
        CC::fgGreen(),
        CC::fgLightGreen());
}

std::string CDefenderCompanion::type() const
{
    return Ressources::Companion::typeAsString(Ressources::Companion::ECompanionType::eDefender);
}

void CDefenderCompanion::preBattle(CEnemy*)
{
    if (_level <= 0)
    {
        return;
    }
    Console::printLn(std::format("{} tries to look dangerous but it does not work. At least it is cute", name()));
}

void CDefenderCompanion::battleAction(CEnemy*, bool&)
{
}

void CDefenderCompanion::postBattle(CEnemy*)
{
    if (_level <= 0)
    {
        return;
    }
    Console::printLn(std::format("{} looks victorious.", name()));
}

int CDefenderCompanion::shield(const int i)
{
    if (_level <= 0)
    {
        return i;
    }
    if (fireDefaultAction())
    {
        Console::printLn(std::format("{} jumps between you and the enemy and protects you.", name()));
        return i - 1;
    }

    return i;
}
