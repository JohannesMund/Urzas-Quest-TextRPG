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

    CSandwich(const std::vector<EIngredients>& ingredients);

    static std::string ingredient2String(const EIngredients ingredient);

    virtual std::string description() const override;

    bool operator==(const CSandwich& other) const
    {
        return _ingredients == other._ingredients;
    }

private:
    std::vector<EIngredients> _ingredients;
};
