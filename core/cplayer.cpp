#include "cplayer.h"
#include "ccompanion.h"
#include "cenemy.h"
#include "cgamemanagement.h"
#include "citem.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "randomizer.h"
#include "ressources.h"

#include <algorithm>
#include <cmath>
#include <format>
#include <string>

CPlayer::CPlayer()
{
    _maxHp = Ressources::Config::maxHp;
    _hp = Ressources::Config::maxHp;
    _gold = Ressources::Config::gold;
    _initiative = Ressources::Config::initiative;
}

void CPlayer::print() const
{

    auto playerString = std::format("{}HP: {}/{} {}Gold: {}", CC::fgGreen(), _hp, _maxHp, CC::fgLightYellow(), _gold);
    auto playerExperience = std::format("Level: {} Experience: {}/{}", _level, _xp, xpForNextLevel());

    if (CGameManagement::getCompanionInstance()->hasCompanion())
    {
        auto companionString = CGameManagement::getCompanionInstance()->name();
        auto companionExperience = std::format("Level: {}", CGameManagement::getCompanionInstance()->level());
        Console::printLnWithSpacer(playerString, companionString);
        Console::printLnWithSpacer(playerExperience, companionExperience);
    }
    else
    {
        Console::printLn(playerString);
        Console::printLn(playerExperience);
    }

    Console::hr();
}

void CPlayer::spendGold(const unsigned int i)
{
    Console::printLn(std::format("You {}spent {} gold{}.", CC::fgLightYellow(), i, CC::ccReset()));
    addGold(i * -1);
}

void CPlayer::loseGold(const unsigned int i)
{
    Console::printLn(std::format("You {}lost {} gold{}.", CC::fgRed(), i, CC::ccReset()));
    addGold(i * -1);
}

void CPlayer::gainGold(const unsigned int i)
{
    Console::printLn(std::format("You {}gained {} gold{}.", CC::fgLightYellow(), i, CC::ccReset()));
    addGold(i);
}

void CPlayer::addGold(const int i)
{
    _gold += i;
    if (_gold < 0)
    {
        _gold = 0;
    }
}

void CPlayer::addHp(const int i)
{
    if (i == 0)
    {
        return;
    }

    if (_hp >= _maxHp)
    {
        Console::printLn(std::format("{}You are fully healed.{}", CC::fgLightGreen(), CC::ccReset()));
        _hp = _maxHp;
        return;
    }

    Console::printLn(std::format("You {} {} Hitpoints.", lostOrGained(i), std::abs(i)));

    _hp += i;
    if (_hp <= 0)
    {
        _hp = 0;
    }
}

void CPlayer::fullHeal()
{
    addHp(_maxHp - _hp);
}

void CPlayer::dealDamage(const int i, const bool bNoShield)
{
    if (i == 0)
    {
        return;
    }

    int damage = i;
    if (bNoShield == false)
    {
        auto items = CGameManagement::getInventoryInstance()->getItemsWithShieldingAction();
        for (auto item : items)
        {
            damage = CGameManagement::getInventoryInstance()->useShieldingAction(item, damage);
        }
    }
    else
    {
        Console::printLn("Your shield cannot help you this time.");
    }
    addHp(damage * -1);
}

void CPlayer::addMaxHp(const int i)
{
    _maxHp += i;
    _hp += i;

    if (_maxHp < Ressources::Config::maxHpMin)
    {
        _maxHp = Ressources::Config::maxHpMin;
    }
    if (i < 0 && _hp > _maxHp)
    {
        _hp = _maxHp;
    }
    Console::printLn(std::format(
        "Your maximum Hitpoints have been {}, you now have {}/{} HP", increasedOrDecreased(i), _hp, _maxHp));
}

bool CPlayer::isDead() const
{
    return _hp <= 0;
}

unsigned int CPlayer::level() const
{
    return _level;
}

int CPlayer::gold() const
{
    return _gold;
}

void CPlayer::addXp(const int i)
{
    Console::printLn(std::format("You {} {} Experience.", lostOrGained(i), std::abs(i)));

    auto xpAvailable = i;
    do
    {
        int xpNeeded = xpForNextLevel() - _xp;
        if (xpNeeded < xpAvailable)
        {
            xpAvailable -= xpNeeded;
            levelUp();
        }
        else
        {
            _xp += xpAvailable;
            xpAvailable = 0;
        }
    } while (xpAvailable);
}

void CPlayer::levelUp()
{
    Console::hr();
    Console::printLn(std::format("{}You gained one level{}", CC::fgLightYellow(), CC::ccReset()),
                     Console::EAlignment::eCenter);
    Console::br();
    _level++;
    _xp = 0;

    fullHeal();
    addMaxHp(Randomizer::getRandom(3) + 1);

    Console::hr();
}

void CPlayer::preBattle(CEnemy* enemy)
{
    auto items = CGameManagement::getInventoryInstance()->getItemsWithBattleEffect();
    for (auto item : items)
    {
        CGameManagement::getInventoryInstance()->useBattleEffect(item, enemy);
    }
    CGameManagement::getCompanionInstance()->preBattle(enemy);

    for (const auto s : _supporters)
    {
        s->preBattle(enemy);
    }
}

std::optional<CBattle::EWeapons> CPlayer::battleAction(CEnemy* enemy, bool& endRound)
{
    if (endRound)
    {
        return {};
    }

    auto items = CGameManagement::getInventoryInstance()->getItemsWithDurableBattleEffect();
    for (auto item : items)
    {
        CGameManagement::getInventoryInstance()->useDurableBattleEffect(item, enemy, endRound);
        if (endRound || enemy->isDead())
        {
            return {};
        }
    }
    CGameManagement::getCompanionInstance()->battleAction(enemy, endRound);
    for (const auto s : _supporters)
    {
        s->battleAction(enemy, endRound);
    }

    if (endRound || enemy->isDead())
    {
        return {};
    }

    while (true)
    {
        CMenu menu;
        CMenu::ActionList weapons = {
            menu.createAction("Rock"), menu.createAction("Paper"), menu.createAction("Scissors")};
        if (enemy->hasExtendedWeaponChoice())
        {
            weapons.push_back(menu.createAction("Lizard"));
            weapons.push_back(menu.createAction("Spock"));
        }

        CMenu::ActionList tools;
        tools.push_back(menu.createAction("Inventory"));
        if (Ressources::Config::superCowPowers)
        {
            tools.push_back(menu.createAction("Win"));
        }
        menu.addMenuGroup(weapons, tools);
        auto input = menu.execute();

        if (input.key == 'r')
        {
            return CBattle::EWeapons::eRock;
        }
        if (input.key == 'p')
        {
            return CBattle::EWeapons::ePaper;
        }
        if (input.key == 's')
        {
            return CBattle::EWeapons::eScissors;
        }
        if (input.key == 'l')
        {
            return CBattle::EWeapons::eLizard;
        }
        if (input.key == 'o')
        {
            return CBattle::EWeapons::eSpock;
        }
        if (input.key == 'i')
        {
            auto item = CGameManagement::getInventoryInstance()->selectItemFromInventory(CInventory::Scope::eBattle);
            if (item.has_value())
            {
                (*item)->useFromBattle(enemy);
            }
        }
        if (input.key == 'w')
        {
            Console::printLn("You use your godlike Powers.");
            enemy->dealDamage(9999);
            endRound = true;
            return {};
        }
    }
    endRound = false;
    return {};
}

void CPlayer::postBattle(CEnemy* enemy)
{
    CGameManagement::getCompanionInstance()->postBattle(enemy);
    for (const auto s : _supporters)
    {
        s->postBattle(enemy);
    }
}

std::string CPlayer::hpAsString() const
{
    return std::format("{}/{}", _hp, _maxHp);
}

unsigned int CPlayer::initiative() const
{
    return _initiative;
}

unsigned int CPlayer::damage() const
{
    auto levelBonus = std::max(static_cast<int>(std::ceil(_level / 5)), 1);
    return 1 + Randomizer::getRandom(levelBonus * 2);
}

void CPlayer::addSupport(CCompanion* support)
{
    _supporters.push_back(support);
}

void CPlayer::removeSupporByName(const std::string_view& name)
{
    auto it = std::remove_if(
        _supporters.begin(), _supporters.end(), [&name](const CCompanion* c) { return c->name() == name; });
    if (it != _supporters.end())
    {
        _supporters.erase(it);
    }
}

unsigned int CPlayer::xpForNextLevel() const
{
    return (_level * 75) * _level * 5;
}

std::string CPlayer::increasedOrDecreased(const int i)
{
    return i < 0 ? "decreased" : "increased";
}

std::string CPlayer::lostOrGained(const int i)
{
    return i < 0 ? std::format("{}lost{}", CC::fgRed(), CC::ccReset())
                 : std::format("{}gained{}", CC::fgLightGreen(), CC::ccReset());
}
