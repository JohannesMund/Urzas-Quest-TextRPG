#pragma once

#include "citem.h"

class CGem : public CItem
{
public:
    CGem();

    static CItem::ItemFilter gemFilter();

protected:
    virtual std::string translatorModuleName() const override;
};
