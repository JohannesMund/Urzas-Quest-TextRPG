#pragma once

#include <citem.h>

class CRabbithatchFood : public CItem
{
public:
    CRabbithatchFood();
    static CItem::ItemFilter fishFilter();

protected:
    virtual std::string translatorModuleName() const override;
};
