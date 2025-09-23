#pragma once

#include "csandwich.h"

#include <nlohmann/json_fwd.hpp>

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

    CBagOfIngredients(const EBagSize size = EBagSize::S);

    static CBagOfIngredients* makeShopItem();
    static CBagOfIngredients* makeLootItem();

    IngredientsList getIngredients() const;
    virtual int buyValue() const override;

    static CItem::ItemFilter CBagOfIngredientsFilter();

private:
    static std::vector<CSandwich::EIngredients> fill(const EBagSize size);
};
