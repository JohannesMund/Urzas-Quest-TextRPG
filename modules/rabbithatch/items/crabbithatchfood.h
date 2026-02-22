#pragma once

#include <citem.h>

class CRabbithatchFood : public CItem
{
public:
    CRabbithatchFood();
    static CItem::ItemFilter rabbitFoodFilter();

protected:
    virtual std::string translatorModuleName() const override;
};
