#pragma once

#include "citem.h"

#include <string>
#include <vector>

class CSandwich : public CItem
{
public:
    enum class EIngredients
    {
        eNone,
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
        eOlives
    };
    CSandwich(const std::vector<EIngredients>& ingredients);

    static std::string ingredient2String(const EIngredients ingredient);

    virtual std::string description() const override;

    std::vector<EIngredients> _ingredients;
};
