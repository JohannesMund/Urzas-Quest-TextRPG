#pragma once

#include "citem.h"
#include "enumiterator.h"

#include <string>
#include <vector>

class CSandwich : public CItem
{
public:
    enum class EIngredients
    {
        eUnknown,
        eSalami,
        ePeperoni,
        eHam,
        eBacon,
        eMortardella,
        eCheddar,
        eEmmental,
        eGouda,
        eMozzarella,
        eLettuce,
        eTomato,
        ePickles,
        eOlives,
    };

    typedef EnumIterator<EIngredients, EIngredients::eUnknown, EIngredients::eOlives> ingredientIterator;
    using IngredientsList = std::vector<EIngredients>;

    CSandwich(const IngredientsList& ingredients);

    virtual std::string description() const override;
    virtual void useFromInventory() override;
    virtual unsigned int buyValue() const override;

    static std::string ingredient2String(const EIngredients ingredient);
    static IngredientsList getListOfAllIngredients();

    bool operator==(const CSandwich& other) const
    {
        return _ingredients == other._ingredients;
    }

private:
    IngredientsList _ingredients;
};
