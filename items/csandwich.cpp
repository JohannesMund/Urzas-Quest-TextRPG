#include "csandwich.h"
#include "colorize.h"

#include <format>

CSandwich::CSandwich(const std::vector<CSandwich::EIngredients>& ingredients) : CItem()
{
    _ingredients = ingredients;
    _isSellable = false;
    _isBuyable = false;
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
    desc.append("Sandwich with: ");

    for (const auto& i : _ingredients)
    {
        desc.append(ingredient2String(i));
        desc.append(", ");
    }

    desc.pop_back();
    desc.pop_back();
    desc.append(".");
    return desc;
}
