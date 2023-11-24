#include "csandwich.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "randomizer.h"

#include <format>

CSandwich::CSandwich(const CSandwich::IngredientsList& ingredients) : CItem()
{
    _ingredients = ingredients;
    _isSellable = false;
    _isBuyable = false;

    _value = 100;

    for (int i = 0; i < ingredients.size(); i++)
    {
        _value += Randomizer::getRandom(25) + 1;
    }
}

std::string CSandwich::ingredient2String(const EIngredients ingredient)
{
    switch (ingredient)
    {
    case EIngredients::eSalami:
        return std::format("{0}S{1}a{0}l{1}a{0}m{1}i{2}", CC::fgLightRed(), CC::fgWhite(), CC::ccReset());
    case EIngredients::ePeperoni:
        return std::format("{0}P{1}e{0}p{1}e{0}r{1}o{0}n{1}i{2}", CC::fgRed(), CC::fgYellow(), CC::ccReset());
    case EIngredients::eHam:
        return std::format("{}Ham{}", CC::fgLightMagenta(), CC::ccReset());
    case EIngredients::eBacon:
        return std::format("{0}B{1}a{0}c{1}o{0}n{2}", CC::fgRed(), CC::fgWhite(), CC::ccReset());
    case EIngredients::eMortardella:
        return std::format("{0}Mo{1}rt{0}ad{1}el{0}la{1}", CC::fgLightMagenta(), CC::fgLightGray(), CC::ccReset());
    case EIngredients::eCheddar:
        return std::format("{}Cheddar{}", CC::fgYellow(), CC::ccReset());
    case EIngredients::eEmmental:
        return std::format("{}Emmental{}", CC::fgLightYellow(), CC::ccReset());
    case EIngredients::eGouda:
        return std::format("{}Gouda{}", CC::fgLightGray(), CC::ccReset());
    case EIngredients::eMozzarella:
        return std::format("{}Mozzarella{}", CC::fgWhite(), CC::ccReset());
    case EIngredients::eLettuce:
        return std::format("{}Lettuce{}", CC::fgLightGreen(), CC::ccReset());
    case EIngredients::eTomato:
        return std::format("{}Tomato{}", CC::fgRed(), CC::ccReset());
    case EIngredients::ePickles:
        return std::format("{0}P{1}i{0}c{1}k{0}l{1}e{0}s{2}", CC::fgGreen(), CC::fgLightGreen(), CC::ccReset());
    case EIngredients::eOlives:
        return std::format("{}Olives{}", CC::fgGreen(), CC::ccReset());
    default:
        return "Whatever that is";
    };
}

std::string CSandwich::ingredients2String(const IngredientsList ingredients)
{
    std::string desc;
    for (const auto& i : ingredients)
    {
        desc.append(ingredient2String(i));
        desc.append(", ");
    }

    desc.pop_back();
    desc.pop_back();
    return desc;
}

CSandwich::IngredientsList CSandwich::getListOfAllIngredients()
{
    IngredientsList ingredients;
    for (auto i : CSandwich::ingredientIterator())
    {
        ingredients.push_back(i);
    }
    return ingredients;
}

std::string CSandwich::description() const
{
    std::string desc = "A ";
    if (_ingredients.size() < 2)
    {
        desc.append("tiny ");
    }
    else if (_ingredients.size() < 5)
    {
        desc.append("small ");
    }
    else if (_ingredients.size() < 8)
    {
        desc.append("medium ");
    }
    else if (_ingredients.size() < 12)
    {
        desc.append("big ");
    }
    else
    {
        desc.append("huge, enormous, gigantic ");
    }
    desc.append(ingredients2String(_ingredients));
    desc.append(".");
    return desc;
}

void CSandwich::useFromInventory()
{
    Console::printLn("The sandwich tastes awesomne and restores your live spirit.");
    unsigned int hp = 0;
    for (auto i : _ingredients)
    {
        if (i == EIngredients::eUnknown)
        {
            Console::printLn(std::format("Eating this {} is a real experience!", ingredient2String(i)));
            CGameManagement::getPlayerInstance()->addXp(Randomizer::getRandom(150) + 50);
        }
        hp += Randomizer::getRandom(3);
    }
    CGameManagement::getPlayerInstance()->addHp(hp);
}

unsigned int CSandwich::buyValue() const
{
    return CItem::buyValue() * 2;
}
