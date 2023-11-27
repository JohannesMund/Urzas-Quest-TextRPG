#include "cbagofingredients.h"
#include "randomizer.h"

#include <format>

CBagOfIngredients::CBagOfIngredients(const EBagSize size) : CSandwich(fill(size))
{

    _isBuyable = true;
    _isSellable = false;
    _isUsableFromInventory = false;

    std::string bagSize;

    switch (size)
    {
    case EBagSize::S:
        bagSize = "small";
        break;
    case EBagSize::M:
        bagSize = "";
        break;
    case EBagSize::L:
        bagSize = "full";
        break;
    case EBagSize::XL:
        bagSize = "jam-packed";
        break;
    case EBagSize::XXL:
        bagSize = "overflowing";
        break;
    }

    _name = std::format("{} Bag of Sandwich Ingredients", bagSize);
}

CBagOfIngredients* CBagOfIngredients::makeShopItem()
{
    auto rnd = Randomizer::getRandom(9);
    if (rnd == 0)
    {
        return new CBagOfIngredients(EBagSize::XXL);
    }
    else if (rnd <= 3)
    {
        return new CBagOfIngredients(EBagSize::XL);
    }
    else if (rnd <= 5)
    {
        return new CBagOfIngredients(EBagSize::L);
    }
    else
    {
        return new CBagOfIngredients(EBagSize::M);
    }
}

CBagOfIngredients* CBagOfIngredients::makeLootItem()
{
    auto rnd = Randomizer::getRandom(5);
    if (rnd == 0)
    {
        return new CBagOfIngredients(EBagSize::L);
    }
    else if (rnd <= 2)
    {
        return new CBagOfIngredients(EBagSize::M);
    }
    else
    {
        return new CBagOfIngredients(EBagSize::S);
    }
}

CSandwich::IngredientsList CBagOfIngredients::getIngredients() const
{
    return _ingredients;
}

unsigned int CBagOfIngredients::buyValue() const
{
    return CSandwich::buyValue() / 2;
}

CItem::ItemFilter CBagOfIngredients::CBagOfIngredientsFilter()
{
    return [](const CItem* item) { return dynamic_cast<const CBagOfIngredients*>(item) != nullptr; };
}

CSandwich::IngredientsList CBagOfIngredients::fill(const EBagSize size)
{
    unsigned int content = 0;

    switch (size)
    {
    case EBagSize::S:
        content = 1 + Randomizer::getRandom(2);
        break;
    case EBagSize::M:
        content = 2 + Randomizer::getRandom(3);
        break;
    case EBagSize::L:
        content = 3 + Randomizer::getRandom(4);
        break;
    case EBagSize::XL:
        content = 4 + Randomizer::getRandom(5);
        break;
    case EBagSize::XXL:
        content = 7 + Randomizer::getRandom(8);
        break;
    }

    auto ingredients = CSandwich::getListOfAllIngredients();

    IngredientsList randomIngredients;
    for (int i = 0; i <= content; i++)
    {
        randomIngredients.push_back(ingredients.at(Randomizer::getRandom(ingredients.size())));
    }

    return randomIngredients;
}
