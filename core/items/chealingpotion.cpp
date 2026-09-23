#include "chealingpotion.h"
#include "cgamemanagement.h"
#include "console.h"
#include "cplayer.h"
#include "randomizer.h"
#include "ressources.h"

#include <format>

CHealingPotion::CHealingPotion(const PotionSize& size) : CItem(TagNames::Item::healingPotion)
{
    std::string sizePrefix;
    std::string descriptionSuffix;

    _description = coreTr("A fancy flask, made of glass with a shimmering, deep-red potion with shiny pink clouds inside. Everything is moving magically, this MUST be a healing potion. Oh, and there is a lable stating \"Potion of Healing\"");

    switch (size)
    {
    case PotionSize::S:
        sizePrefix = "Small ";
        descriptionSuffix = coreTr("\nThe bottle is tiny and not completely full.");
        _value = 50;
        break;
    case PotionSize::M:
    default:
        _value = 75;
        break;
    case PotionSize::L:
        sizePrefix = "Large ";
        descriptionSuffix = coreTr("\nThe bottle is pretty big.");
        _value = 150;
        break;
    case PotionSize::XL:
        sizePrefix = "Huge ";
        descriptionSuffix = coreTr("\nTHe bottle is huge, and filled to the brim.");
        _value = 500;
        break;
    }

    std::string name = coreTr("Potion of Healing");
    if (!sizePrefix.empty())
    {
        name = sizePrefix + name;
    }
    if (!descriptionSuffix.empty())
    {
        _description.append(descriptionSuffix);
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
    Console::printLn(coreTr("You open the bottle, and swallow it in one draw. Healing potions are disgusting!"));
    use();
}

void CHealingPotion::useFromBattle(CEnemy*)
{
    Console::printLn(coreTr("It is in the middle of a hot fight, but you need healing."));
    use();
}

nlohmann::json CHealingPotion::save() const
{
    nlohmann::json o = CItem::save();
    o["size"] = _size;
    return o;
}

void CHealingPotion::load(const nlohmann::json& o)
{
    CItem::load(o);
    _size = o["size"];
}

std::string CHealingPotion::translatorModuleName() const
{
    return std::string();
}

void CHealingPotion::use()
{
    unsigned int hp;
    switch (_size)
    {
    case PotionSize::S:
        Console::printLn(coreTr("Fortunately, it is not much, You feel a little refreshed!"));
        hp = 1;
        break;
    case PotionSize::M:
    default:
        hp = Randomizer::getRandom(2) + 1;
        break;
    case PotionSize::L:
        Console::printLn(coreTr("Sooo much potion! But it was worth it, you feel really very refreshed!"));
        hp = Randomizer::getRandom(9) + 1;
        break;
    case PotionSize::XL:
        Console::printLn(coreTr("You are flooded by a burst of life! you feel like a new born!"));
        hp = 99999;
        break;
    }
    CGameManagement::getPlayerInstance()->addHp(hp);
}
