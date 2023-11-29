#include "citem.h"
#include "cequipment.h"
#include "console.h"

#include <cmath>
#include <format>

using namespace std;

CItem::CItem()
{
}

void CItem::view()
{
    Console::hr();
    Console::printLn(format("You decide to take a look at: {}", _name));
    Console::printLn(description());
}

bool CItem::isUsableFromInventory() const
{
    return _isUsableFromInventory;
}

bool CItem::isUsableFromBattle() const
{
    return _isUsableFromBattle;
}

bool CItem::hasDeathEffect() const
{
    return _hasDeathEffect;
}

bool CItem::hasBattleEffect() const
{
    return _hasBattleEffect;
}

bool CItem::hasDurableBattleEffect() const
{
    return _hasBattleBuff;
}

bool CItem::hasShieldingAction() const
{
    return _hasShieldingAction;
}

bool CItem::isConsumable() const
{
    return _isConsumable;
}

CItem::ItemFilter CItem::nameFilter(const std::string& name)
{
    return [name](const CItem* item) { return item->name().compare(name) == 0; };
}

CItem::ItemFilter CItem::battleEffectFilter()
{
    return [](const CItem* item) { return item->hasBattleEffect(); };
}

CItem::ItemFilter CItem::durableBattleEffectFilter()
{
    return [](const CItem* item) { return item->hasDurableBattleEffect(); };
}

CItem::ItemFilter CItem::shieldingActionFilter()
{
    return [](const CItem* item) { return item->hasShieldingAction(); };
}

CItem::ItemFilter CItem::deathEffectFilter()
{
    return [](const CItem* item) { return item->hasDeathEffect(); };
}

string CItem::name() const
{
    return _name;
}

string CItem::description() const
{
    return _description;
}

bool CItem::isSellable() const
{
    return _isSellable;
}

unsigned int CItem::value() const
{
    return _value;
}

unsigned int CItem::buyValue() const
{
    return std::floor(value() * 1.5);
}
