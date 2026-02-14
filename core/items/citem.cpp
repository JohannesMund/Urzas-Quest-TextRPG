#include "citem.h"
#include "cequipment.h"
#include "console.h"
#include "translator/ctranslator.h"

#include <cmath>
#include <format>
#include <nlohmann/json.hpp>

using namespace std;

CItem::CItem(const std::string_view& objectName) : CGameStateObject(objectName)
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

nlohmann::json CItem::save() const
{
    nlohmann::json o;

    o["name"] = _name;
    o["description"] = _description;

    o["isUsableFromInventory"] = _isUsableFromInventory;
    o["isUsableFromBattle"] = _isUsableFromBattle;

    o["hasDeathEffect"] = _hasDeathEffect;
    o["hasBattleEffect"] = _hasBattleEffect;
    o["hasBattleBuff"] = _hasBattleBuff;
    o["hasShieldingAction"] = _hasShieldingAction;

    o["isSellable"] = _isSellable;
    o["isBuyable"] = _isBuyable;
    o["value"] = _value;
    o["isConsumable"] = _isConsumable;

    return o;
}

std::string_view CItem::translatorObjectName() const
{
    return TagNames::Item::item;
}

std::string_view CItem::translatorModuleName() const
{
    return std::string_view();
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

int CItem::buyValue() const
{
    return static_cast<int>(std::floor(value() * 1.5));
}
