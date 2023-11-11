#include "cplayer.h"
#include "cenemy.h"
#include "cgamemanagement.h"
#include "citem.h"
#include "cmenu.h"
#include "colorconsole.h"
#include "console.h"
#include "ressources.h"

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

void CPlayer::addGold(const int i)
{
    Console::printLn(std::format("You {} {} gold.", lostOrGained(i), std::abs(i)));
    _gold += i;
}

void CPlayer::addHp(const int i)
{
    Console::printLn(std::format("You {} {} Hitpoints.", lostOrGained(i), std::abs(i)));
    _hp += i;
    if (_hp <= 0)
    {
        _hp = 0;
    }
    if (_hp > _maxHp)
    {
        _hp = _maxHp;
    }
}

void CPlayer::dealDamage(const int i, const bool bNoShield)
{
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
    _xp += i;

    if (_xp > xpForNextLevel())
    {
        levelUp();
    }
}

void CPlayer::levelUp()
{
    Console::printLn("You gained one level");
    _level++;
}

void CPlayer::preBattle(CEnemy* enemy)
{
    auto items = CGameManagement::getInventoryInstance()->getItemsWithBattleEffect();
    for (auto item : items)
    {
        CGameManagement::getInventoryInstance()->useBattleEffect(item, enemy);
    }
    CGameManagement::getCompanionInstance()->preBattle(enemy);
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
    if (endRound || enemy->isDead())
    {
        return {};
    }

    while (true)
    {
        CMenu menu;
        std::vector<CMenu::Action> weapons = {
            menu.createAction("Rock"), menu.createAction("Paper"), menu.createAction("Scissors")};
        if (enemy->hasExtendedWeaponChoice())
        {
            weapons.push_back(menu.createAction("Lizard"));
            weapons.push_back(menu.createAction("Spock"));
        }

        menu.addMenuGroup(weapons, {menu.createAction("Inventory"), menu.createAction("Win")});
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
}

std::string CPlayer::hpAsString() const
{
    return std::format("{}/{}", _hp, _maxHp);
}

unsigned int CPlayer::initiative() const
{
    return _initiative;
}

unsigned int CPlayer::xpForNextLevel() const
{
    return Ressources::Config::getXpForLevel(_level);
}

std::string CPlayer::increasedOrDecreased(const int i)
{
    return i < 0 ? "decreased" : "increased";
}

std::string CPlayer::lostOrGained(const int i)
{
    return i < 0 ? "lost" : "gained";
}
