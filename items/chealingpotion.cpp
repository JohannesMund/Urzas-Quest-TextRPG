#include "chealingpotion.h"
#include "cgamemanagement.h"
#include "console.h"
#include "cplayer.h"
#include "randomizer.h"
#include "ressources.h"

#include <format>

CHealingPotion::CHealingPotion(const PotionSize& size) : CItem()
{
    std::string name = "Potion of Healing";
    _description = "A fancy flask, made of glass with a shimmering, deep-red potion with shiny pink clouds inside. "
                   "Everything is moving magically, this MUST be a healing potion. Oh, and there is a lable stating "
                   "\"Potion of Healing\"";

    switch (size)
    {
    case PotionSize::S:
        name = "Small " + name;
        _description.append("\nThe bottle is tiny and not completely full.");
        _value = 50;
        break;
    case PotionSize::M:
    default:
        _value = 75;
        break;
    case PotionSize::L:
        name = "Large " + name;
        _description.append("\nThe bottle is pretty big.");
        _value = 150;
        break;
    case PotionSize::XL:
        name = "Huge " + name;
        _description.append("\nTHe bottle is huge, and filled to the brim.");
        _value = 500;
        break;
    }
    _name = std::format("{}{}{}", CC::fgLightBlue(), name, CC::ccReset());
    _size = size;
    _isConsumable = true;
    _isUsableFromInventory = true;
    _isUsableFromBattle = true;
    _isSellable = true;
}

void CHealingPotion::useFromInventory()
{
    Console::printLn("You open the bottle, and swallow it in one draw. Healing potions are disgusting!");
    use();
}

void CHealingPotion::useFromBattle(CEnemy*)
{
    Console::printLn("It is in the middle of a hot fight, but you need healing.");
    use();
}

void CHealingPotion::use()
{
    unsigned int hp;
    switch (_size)
    {
    case PotionSize::S:
        Console::printLn("Fortunately, it is not much, You feel a little refreshed!");
        hp = 1;
        break;
    case PotionSize::M:
    default:
        hp = Randomizer::getRandom(2) + 1;
        break;
    case PotionSize::L:
        Console::printLn("Sooo much potion! But it was worth it, you feel really very refreshed!");
        hp = Randomizer::getRandom(9) + 1;
        break;
    case PotionSize::XL:
        Console::printLn("You are flooded by a burst of life! you feel like a new born!");
        hp = 99999;
        break;
    }
    CGameManagement::getPlayerInstance()->addHp(hp);
}
