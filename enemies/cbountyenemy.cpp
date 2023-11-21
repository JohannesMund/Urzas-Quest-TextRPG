#include "cbountyenemy.h"
#include "cgamemanagement.h"
#include "citemfactory.h"
#include "console.h"
#include "randomizer.h"
#include "ressources.h"

CBountyEnemy::CBountyEnemy(const std::string& name) : CEnemy()
{
    _name = name;
    _weapon = Ressources::Enemies::getRandomEnemyWeapon();
    _extendedWeaponChoice = true;

    _level = CGameManagement::getPlayerInstance()->level() + Randomizer::getRandom(2);
    _hp = 3 + (_level * Randomizer::getRandom(3));
}

void CBountyEnemy::spoilsOfWar() const
{
    CGameManagement::getPlayerInstance()->addXp(_level * 200);
    Console::printLn("Obviously, crime does pay off.");
    CGameManagement::getPlayerInstance()->addGold(Randomizer::getRandom(_level * 100) + _level * 33);

    auto amount = Randomizer::getRandom(2);
    {
        for (auto i = 0; i <= amount; i++)
        {
            CGameManagement::getInventoryInstance()->addShopItem();
        }
    }
}

void CBountyEnemy::battleAction(bool& endRound)
{
    CEnemy::battleAction(endRound);
}
