#include "cenemy.h"
#include "cgamemanagement.h"
#include "colorconsole.h"
#include "console.h"
#include "itemfactory.h"
#include "randomizer.h"

#include <format>

CEnemy::CEnemy()
{
}

void CEnemy::preBattle()
{
}

void CEnemy::preBattleAction()
{
    _battleDecision = {};
}

void CEnemy::battleAction(bool& endRound)
{
    if (endRound)
    {
        return;
    }

    int range = _extendedWeaponChoice ? 5 : 3;
    _battleDecision = static_cast<CBattle::EWeapons>(Randomizer::getRandom(range));

    endRound = false;
}

void CEnemy::postBattleAction()
{
}

void CEnemy::postBattle()
{
}

void CEnemy::spoilsOfWar() const
{
    CGameManagement::getPlayerInstance()->addXp(basicXP(_level));

    if (Randomizer::getRandom(2) == 0)
    {
        Console::printLn("Your enemy seems to be rich. At least he has a bag of gold.");
        CGameManagement::getPlayerInstance()->addGold(Randomizer::getRandom(_level * 33) + _level * 25);
    }

    if (Randomizer::getRandom(3) < 2)
    {
        Console::printLn("This one collected stuff, you grab what you can.");
        do
        {
            CGameManagement::getInventoryInstance()->addItem(ItemFactory::makeItem(ItemFactory::EItemType::eJunkItem));
        } while (Randomizer::getRandom(2) == 0);
    }
}

std::string CEnemy::name() const
{
    return _name;
}

std::string CEnemy::weapon() const
{
    return _weapon;
}

unsigned int CEnemy::level() const
{
    return _level;
}

unsigned int CEnemy::damage() const
{
    auto levelBonus = std::max((int)std::ceil(_level / 5), 1);
    return 1 + Randomizer::getRandom(levelBonus);
}

unsigned int CEnemy::initiative() const
{
    return _initiative;
}

bool CEnemy::isDead() const
{
    return _hp <= 0;
}

bool CEnemy::hasExtendedWeaponChoice() const
{
    return _extendedWeaponChoice;
}

void CEnemy::addHp(const int i)
{
    _hp += i;
    if (_hp < 0)
    {
        _hp = 0;
    }
}

void CEnemy::dealDamage(const int i)
{
    if (i == 0)
    {
        return;
    }
    Console::printLn(std::format("You hit the enemy for {}{} damage{}.", CC::fgLightBlue(), i, CC::ccReset()));
    addHp(i * -1);
}

unsigned int CEnemy::hp() const
{
    return _hp;
}

std::optional<CBattle::EWeapons> CEnemy::peek()
{
    return _battleDecision;
}

void CEnemy::printBossBattleHeader() const
{
    Console::cls();
    Console::printLn("Boss Battle", Console::EAlignment::eCenter);
    Console::printLn(_name, Console::EAlignment::eCenter);
    Console::br();
}

unsigned int CEnemy::basicXP(const unsigned int level)
{
    return Randomizer::getRandom(level * 75) + level * 75;
}
