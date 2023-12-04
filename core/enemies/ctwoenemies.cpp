#include "ctwoenemies.h"
#include "cmenu.h"
#include "console.h"

#include <format>

CTwoEnemies::CTwoEnemies(std::string name1, std::string name2) : CEnemy()
{
    _name1 = name1;
    _name2 = name2;
}

void CTwoEnemies::preBattleAction()
{
    if (_hp1 > 0 && _hp2 <= 0)
    {
        _currentTarget = EWho::eEnemy1;
        return;
    }
    if (_hp1 <= 0 && _hp2 > 0)
    {
        _currentTarget = EWho::eEnemy2;
        return;
    }

    _lastHp = _hp;
    Console::printLn("Who do you attack?");
    CMenu menu;
    menu.addMenuGroup({menu.createAction(_name1, '1')}, {menu.createAction(_name2, '2')});
    if (menu.execute().key == 'b')
    {
        _currentTarget = EWho::eEnemy1;
    }
    else
    {
        _currentTarget = EWho::eEnemy2;
    }
}

void CTwoEnemies::battleAction(bool&)
{
    if (_currentTarget == EWho::eEnemy1)
    {
        if (_hp2 > 0)
        {
            passiveBattleAction(EWho::eEnemy2);
        }
    }
    else
    {
        if (_hp1 > 0)
        {
            passiveBattleAction(EWho::eEnemy1);
        }
    }
}

void CTwoEnemies::postBattleAction()
{
    const int damage = _lastHp - _hp;
    if (damage > 0)
    {
        if (_currentTarget == EWho::eEnemy1)
        {
            _hp1 -= damage;
            if (_hp1 <= 0)
            {
                Console::printLn(std::format("You defeated {}", _name1));
            }
        }
        else
        {
            _hp2 -= damage;
            if (_hp2 <= 0)
            {
                Console::printLn(std::format("You defeated {}", _name2));
            }
        }
    }
}

std::string CTwoEnemies::name() const
{
    return std::format("{} and {}", _name1, _name2);
}
