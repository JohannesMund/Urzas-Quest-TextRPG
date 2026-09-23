#include "cbomb.h"
#include "cenemy.h"
#include "colorize.h"
#include "console.h"

#include <format>
#include <nlohmann/json.hpp>

CBomb::CBomb(const BombSize& size) : CItem(TagNames::Item::bomb)
{
    std::string name;
    switch (size)
    {
    case BombSize::S:
        name = coreTr("Fire cracker");
        _description = coreTr("A pretty little fire creacker.");
        _value = 50;
        break;
    case BombSize::M:
    default:
        name = coreTr("Cherry bomb");
        _description = coreTr("two little cherries, one big boOOM.");
        _value = 100;
        break;
    case BombSize::L:
        name = coreTr("Pirate bomb");
        _description = coreTr("Lig in the pirate movies, big, and... bomby.");
        _value = 250;
        break;
    case BombSize::XL:
        name = coreTr("tactical nuclear bomb");
        _description = coreTr("Nukelear, it is pronounced nukelear");
        _value = 500;
        break;
    }

    _name = std::format("{}{}{}", CC::fgLightRed(), name, CC::ccReset());
    _size = size;
    _isConsumable = true;
    _isUsableFromBattle = true;
    _isSellable = true;
}

void CBomb::useFromBattle(CEnemy* enemy)
{
    Console::printLn(coreTr("You throw {} at {}. The Boom is spectacular!", _name, enemy->name()));

    unsigned int damage;
    switch (_size)
    {
    case BombSize::S:
        damage = 1;
        break;
    case BombSize::M:
    default:
        damage = 3;
        break;
    case BombSize::L:
        damage = 5;
        break;
    case BombSize::XL:
        damage = 15;
        break;
    }

    Console::printLn(coreTr("{} is hit for {} damage.", enemy->name(), damage));
    enemy->dealDamage(damage);
}

nlohmann::json CBomb::save() const
{
    nlohmann::json o = CItem::save();
    o["size"] = _size;
    return o;
}

void CBomb::load(const nlohmann::json& o)
{
    CItem::load(o);
    _size = o["size"];
}

std::string CBomb::translatorModuleName() const
{
    return std::string();
}
