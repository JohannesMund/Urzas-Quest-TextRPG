#pragma once

#include "csandwich.h"

class CShaggysSandwich : public CSandwich
{
public:
    CShaggysSandwich();

    static CItem::ItemFilter shaggysSandwichFilter();

protected:
    virtual std::string translatorModuleName() const override;
};
