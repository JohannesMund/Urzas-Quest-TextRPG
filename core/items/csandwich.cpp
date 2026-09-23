#include "csandwich.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "randomizer.h"
#include "translator/ctranslator.h"
#include "json/jsontagnames.h"

#include <format>

CSandwich::CSandwich(const CSandwich::IngredientsList& ingredients, const std::string_view& objectName) :
    CItem(objectName)
{
    _ingredients = ingredients;
    _isSellable = false;
    _isBuyable = false;

    _value = 100;

    for (auto i = 0U; i < ingredients.size(); i++)
    {
        _value += Randomizer::getRandom(25) + 1;
    }
}

namespace
{
std::string sandwichTr(const std::string_view& textId)
{
    return CTranslator::tr(TagNames::Translator::core, TagNames::Item::item, textId);
}
} // namespace

std::string CSandwich::ingredient2String(const EIngredients ingredient)
{
    switch (ingredient)
    {
    case EIngredients::eSalami:
        // Note: keeping original color pattern for visual consistency (not translated, see decorative letter-coloring)
        return std::format("{0}S{1}a{0}l{1}a{0}m{1}i{2}", CC::fgLightRed(), CC::fgWhite(), CC::ccReset());
    case EIngredients::ePeperoni:
        // Note: keeping original color pattern for visual consistency (not translated, see decorative letter-coloring)
        return std::format("{0}P{1}e{0}p{1}e{0}r{1}o{0}n{1}i{2}", CC::fgRed(), CC::fgYellow(), CC::ccReset());
    case EIngredients::eHam:
        return std::format("{}{}{}", CC::fgLightMagenta(), sandwichTr("Ham"), CC::ccReset());
    case EIngredients::eBacon:
        // Note: keeping original color pattern for visual consistency (not translated, see decorative letter-coloring)
        return std::format("{0}B{1}a{0}c{1}o{0}n{2}", CC::fgRed(), CC::fgWhite(), CC::ccReset());
    case EIngredients::eMortardella:
        // Note: keeping original color pattern for visual consistency (not translated, see decorative letter-coloring)
        return std::format("{0}Mo{1}rt{0}ad{1}el{0}la{1}", CC::fgLightMagenta(), CC::fgLightGray(), CC::ccReset());
    case EIngredients::eCheddar:
        return std::format("{}{}{}", CC::fgYellow(), sandwichTr("Cheddar"), CC::ccReset());
    case EIngredients::eEmmental:
        return std::format("{}{}{}", CC::fgLightYellow(), sandwichTr("Emmental"), CC::ccReset());
    case EIngredients::eGouda:
        return std::format("{}{}{}", CC::fgLightGray(), sandwichTr("Gouda"), CC::ccReset());
    case EIngredients::eMozzarella:
        return std::format("{}{}{}", CC::fgWhite(), sandwichTr("Mozzarella"), CC::ccReset());
    case EIngredients::eLettuce:
        return std::format("{}{}{}", CC::fgLightGreen(), sandwichTr("Lettuce"), CC::ccReset());
    case EIngredients::eTomato:
        return std::format("{}{}{}", CC::fgRed(), sandwichTr("Tomato"), CC::ccReset());
    case EIngredients::ePickles:
        // Note: keeping original color pattern for visual consistency (not translated, see decorative letter-coloring)
        return std::format("{0}P{1}i{0}c{1}k{0}l{1}e{0}s{2}", CC::fgGreen(), CC::fgLightGreen(), CC::ccReset());
    case EIngredients::eOlives:
        return std::format("{}{}{}", CC::fgGreen(), sandwichTr("Olives"), CC::ccReset());
    default:
        return std::format("{}{}{}", CC::fgLightMagenta(), sandwichTr("Whatever that is"), CC::ccReset());
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

nlohmann::json CSandwich::save() const
{
    nlohmann::json o = CItem::save();
    nlohmann::json ingredients = nlohmann::json::array();
    for (auto i : _ingredients)
    {
        ingredients.push_back(i);
    }
    o["ingredients"] = ingredients;
    return o;
}

void CSandwich::load(const nlohmann::json& o)
{
    CItem::load(o);
    for (auto i : o["ingredients"])
    {
        _ingredients.push_back(i);
    }
}

std::string CSandwich::translatorModuleName() const
{
    return std::string();
}

std::string CSandwich::description() const
{
    std::string sizeDesc;
    if (_ingredients.size() < 2)
    {
        sizeDesc = coreTr("A tiny sandwich with: ");
    }
    else if (_ingredients.size() < 5)
    {
        sizeDesc = coreTr("A small sandwich with: ");
    }
    else if (_ingredients.size() < 8)
    {
        sizeDesc = coreTr("A medium sandwich with: ");
    }
    else if (_ingredients.size() < 12)
    {
        sizeDesc = coreTr("A big sandwich with: ");
    }
    else
    {
        sizeDesc = coreTr("A huge, enormous, gigantic sandwich with: ");
    }

    std::string desc = sizeDesc;
    desc.append(ingredients2String(_ingredients));
    desc.append(coreTr("."));
    return desc;
}

void CSandwich::useFromInventory()
{
    Console::printLn(coreTr("The sandwich tastes awesomne and restores your live spirit."));
    unsigned int hp = 0;
    for (auto i : _ingredients)
    {
        if (i == EIngredients::eUnknown)
        {
            Console::printLn(coreTr("Eating this {} is a real experience!", ingredient2String(i)));
            CGameManagement::getPlayerInstance()->addXp(Randomizer::getRandom(150) + 50);
        }
        hp += Randomizer::getRandom(3);
    }
    CGameManagement::getPlayerInstance()->addHp(hp);
}

int CSandwich::buyValue() const
{
    return CItem::buyValue() * 2;
}
