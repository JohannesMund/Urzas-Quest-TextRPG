#include "cbomb.h"
#include "cenemy.h"
#include "colorize.h"
#include "console.h"

#include <format>

CBomb::CBomb(const BombSize& size)
{
    std::string name;
    switch (size)
    {
    case BombSize::S:
        name = "Fire cracker";
        _description.append("A pretty little fire creacker.");
        _value = 50;
        break;
    case BombSize::M:
    default:
        name = "Cherry bomb";
        _description.append("two little cherries, one big boOOM.");
        _value = 100;
        break;
    case BombSize::L:
        name = "Pirate bomb";
        _description.append("Lig in the pirate movies, big, and... bomby.");
        _value = 250;
        break;
    case BombSize::XL:
        name = "tactical nuclear bomb";
        _description.append("Nukelear, it is pronounced nukelear");
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
    Console::printLn(std::format("You throw {} at {}. The Boom is spectacular!", _name, enemy->name()));

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

    Console::printLn(std::format("{} is hit for {} damage.", enemy->name(), damage));
    enemy->dealDamage(damage);
}
