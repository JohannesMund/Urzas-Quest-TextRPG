#include "cleilacompanion.h"
#include "../moduleressources.h"

#include "cenemy.h"
#include "cgamemanagement.h"
#include "console.h"
#include "randomizer.h"
#include "ressources.h"

#include <format>

CLeilaCompanion::CLeilaCompanion() : CSupportCompanion(LeilaRescue::moduleName(), TagNames::LeilaRescue::leilaCompanion)
{
    _level = 5;
}

std::string CLeilaCompanion::name() const
{
    return Ressources::Game::leila();
}

void CLeilaCompanion::preBattle(CEnemy*)
{
    Console::printLn(tr(
        "Like Lois and Clark, like Bonny and Clyde, like Romeo and Juliet. You and {} fight together, side by side.",
        name()));
}

void CLeilaCompanion::battleAction(CEnemy* enemy, bool&)
{
    if (fireDefaultAction())
    {
        Console::printLn(tr("{} attacks the enemy and deals 1 damage.", name()));
        enemy->dealDamage(1);
    }
    else
    {
        Console::printLn(tr("{} holds his weapon and looks dangerous.", name()));
    }
}

void CLeilaCompanion::postBattle(CEnemy*)
{
    if (fireDefaultAction())
    {
        Console::printLn(tr("{} cares a little bit for your wouds", name()));
        CGameManagement::getPlayerInstance()->addHp(1);
    }
    else
    {
        Console::printLn(tr("{} looks victorious.", name()));
    }
}

void CLeilaCompanion::joinText() const
{
    Console::printLn(tr("Your dreams come true, {} decides to join forces with you!", name()));
}

void CLeilaCompanion::leaveText() const
{
    Console::printLn(tr("After some great time together, {} leaves your side to return to the Rebellion", name()));
}
