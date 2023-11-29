#include "chealercompanion.h"
#include "cgamemanagement.h"
#include "console.h"
#include "ressources.h"

#include <format>

CHealerCompanion::CHealerCompanion()
{
}

std::string CHealerCompanion::name() const
{
    return CC::colorizeString(
        Ressources::Companion::nameForCompanionType(Ressources::Companion::ECompanionType::eHealer, _level),
        CC::fgBlue(),
        CC::fgLightBlue());
}

std::string CHealerCompanion::type() const
{
    return Ressources::Companion::typeAsString(Ressources::Companion::ECompanionType::eHealer);
}

void CHealerCompanion::preBattle(CEnemy* enemy)
{
    if (_level <= 0)
    {
        return;
    }
    Console::printLn(std::format("{} tries to look dangerous but it does not work. At least it is cute", name()));
}

void CHealerCompanion::battleAction(CEnemy* enemy, bool& endRound)
{
}

void CHealerCompanion::postBattle(CEnemy* enemy)
{
    if (_level <= 0)
    {
        return;
    }
    if (fireDefaultAction())
    {
        Console::printLn(std::format("{} cares a little bit for your wouds", name()));
        CGameManagement::getPlayerInstance()->addHp(1);
    }
    else
    {
        Console::printLn(std::format("{} looks victorious.", name()));
    }
}

int CHealerCompanion::shield(const int i)
{
    return i;
}
