#include "cenemyhorde.h"
#include "cgamemanagement.h"
#include "console.h"
#include "randomizer.h"

#include <format>
CEnemyHorde::CEnemyHorde(const unsigned int count, const unsigned int minHp, const unsigned int maxHp) : CEnemy()
{
    _count = count;
    for (unsigned int i = 0; i < count; i++)
    {
        auto hp = Randomizer::getRandom(maxHp - minHp) + minHp;
        _hps.push_back(hp);
        _hp += hp;
    }
}

void CEnemyHorde::preBattleAction()
{
    _lastHp = _hp;
}

void CEnemyHorde::battleAction(bool&)
{
    _attacks = 0;
    unsigned int counter = 0;
    for (unsigned int i = 1; i < _hps.size(); i++)
    {
        if (i <= 0)
        {
            continue;
        }
        counter++;
        if (counter >= _simultaneousAttacks)
        {
            break;
        }

        if (Randomizer::getRandom(3) == 0)
        {
            Console::printLn(std::format("While you are fighting, another {} hits you.", _name));
            _attacks++;
        }
    }
}

void CEnemyHorde::postBattleAction()
{
    auto damageDealt = _lastHp - _hp;
    if (damageDealt <= 0)
    {
        return;
    }

    if (_hps.size())
    {
        auto tmpHp = _hps.at(0);
        if (damageDealt > tmpHp)
        {
            damageDealt = tmpHp;
        }

        _hps.at(0) -= damageDealt;
        _hp = _lastHp - damageDealt;
    }
    removeDeadEnemies();
}

unsigned int CEnemyHorde::damage() const
{
    return CEnemy::damage() * (_attacks + 1);
}

std::string CEnemyHorde::name() const
{
    return std::format("A horde of {}s", _name);
}

void CEnemyHorde::removeDeadEnemies()
{
    auto it = std::remove_if(_hps.begin(), _hps.end(), [](const int nbr) { return nbr <= 0; });
    if (it != _hps.end())
    {
        _hps.erase(it);
    }
    if (_hps.size() == 0)
    {
        _hp = 0;
    }
}
