#pragma once

#include "csandwich.h"

class CBagOfIngredients : public CSandwich
{

public:
    enum class EBagSize
    {
        S,
        M,
        L,
        XL,
        XXL
    };

    CBagOfIngredients(const EBagSize size);

    static CBagOfIngredients* makeShopItem();
    static CBagOfIngredients* makeLootItem();

    virtual unsigned int buyValue() const override;

    static CItem::ItemFilter CBagOfIngredientsFilter();

private:
    static std::vector<CSandwich::EIngredients> fill(const EBagSize size);
};
