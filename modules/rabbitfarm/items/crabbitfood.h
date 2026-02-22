#pragma once

#include <citem.h>

class CRabbitFood : public CItem
{
public:
    CRabbitFood();
    static CItem::ItemFilter rabbitFoodFilter();

protected:
    virtual std::string translatorModuleName() const override;
};
