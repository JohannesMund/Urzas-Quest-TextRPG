#include "cleilacompanion.h"
#include "cenemy.h"
#include "cgamemanagement.h"
#include "console.h"
#include "randomizer.h"
#include "ressources.h"

#include <format>

CLeilaCompanion::CLeilaCompanion() : CCompanion()
{
    _level = 5;
}

std::string CLeilaCompanion::name() const
{
    return Ressources::Game::leila();
}

std::string CLeilaCompanion::type() const
{
    return Ressources::Companion::typeAsString(Ressources::Companion::ECompanionType::eScaryMonster);
}

void CLeilaCompanion::preBattle(CEnemy*)
{
    Console::printLn(std::format(
        "Like Lois and Clark, like Bonny and Clyde, like Romeo and Juliet. You and {} fight together, side by side.",
        name()));
}

void CLeilaCompanion::battleAction(CEnemy* enemy, bool&)
{
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

void CLeilaCompanion::postBattle(CEnemy*)
{
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

int CLeilaCompanion::shield(const int i)
{
    return i;
}
