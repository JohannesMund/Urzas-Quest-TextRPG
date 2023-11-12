#include "clakeoftearsboss.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"
#include "moduleressources.h"
#include "randomizer.h"

#include <format>

CLakeOfTearsBoss::CLakeOfTearsBoss()
{
    _name = LakeTearsRessources::getColoredBossString();
    _weapon = "Crocodile Tears of Despair";
    _extendedWeaponChoice = true;

    _level = CGameManagement::getPlayerInstance()->level() + 2;
    _hp1 = Randomizer::getRandom(5) + 1 + (_level * Randomizer::getRandom(2) + 3);
    _hp2 = Randomizer::getRandom(2) + 3 + (_level * Randomizer::getRandom(4) + 1);
    _hp = _hp1 + _hp2;
}

void CLakeOfTearsBoss::spoilsOfWar() const
{
    CGameManagement::getPlayerInstance()->addXp(_level * 400);
    CGameManagement::getPlayerInstance()->addXp(_level * 400);
    Console::printLn("As expected they have nothing. You feel sad, dirty and just want to go.");
}

void CLakeOfTearsBoss::preBattleAction()
{
    if (_hp1 > 0 && _hp2 <= 0)
    {
        _currentTarget = EWho::eBimmelchen;
        return;
    }
    if (_hp1 <= 0 && _hp2 > 0)
    {
        _currentTarget = EWho::ePimmelchen;
        return;
    }

    _lastHp = _hp;
    Console::printLn("Who do you attack?");
    CMenu menu;
    menu.addMenuGroup({menu.createAction(LakeTearsRessources::bimmelchen(), 'b')},
                      {menu.createAction(LakeTearsRessources::pimmelchen(), 'p')});
    if (menu.execute().key == 'b')
    {
        _currentTarget = EWho::eBimmelchen;
    }
    else
    {
        _currentTarget = EWho::ePimmelchen;
    }
}

void CLakeOfTearsBoss::battleAction(bool& endRound)
{
    if (_currentTarget == EWho::eBimmelchen)
    {
        if (_hp2 > 0)
        {
            auto dmg = Randomizer::getRandom(3);
            if (dmg > 0)
            {
                Console::printLn(std::format("{} attacks you", LakeTearsRessources::pimmelchen()));
                CGameManagement::getPlayerInstance()->dealDamage(dmg);
            }
        }
    }

    if (_currentTarget == EWho::ePimmelchen)
    {
        if (_hp1 > 0)
        {
            auto dmg = Randomizer::getRandom(3);
            if (dmg > 0)
            {
                Console::printLn(std::format("{} attacks you", LakeTearsRessources::bimmelchen()));
                CGameManagement::getPlayerInstance()->dealDamage(dmg);
            }
        }
    }
}

void CLakeOfTearsBoss::postBattleAction()
{
    const int damage = _lastHp - _hp;
    if (damage > 0)
    {
        if (_currentTarget == EWho::eBimmelchen)
        {
            _hp1 -= damage;
            if (_hp1 <= 0)
            {
                Console::printLn(std::format("You killed {}", LakeTearsRessources::bimmelchen()));
            }
        }
        else
        {
            _hp2 -= damage;
            if (_hp2 <= 0)
            {
                Console::printLn(std::format("You killed {}", LakeTearsRessources::pimmelchen()));
            }
        }
    }
}
