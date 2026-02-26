#pragma once

#include "cbasicdjinn.h"

class CGenie : public CBasicDjinn
{
public:
    CGenie();

    virtual void talk() override;

    virtual std::string name() const override;
    virtual std::string describe() const override;

    virtual CMenuAction npcNav(CMenu& menu) const override;

private:
    void printHeader(const bool bFull = true) const override;
};