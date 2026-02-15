#pragma once

#include "citem.h"

class CHeartContainer : public CItem
{
public:
    CHeartContainer();
    virtual void useFromInventory() override;

protected:
    virtual std::string translatorModuleName() const override;
};
