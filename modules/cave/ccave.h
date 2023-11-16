#pragma once

#include "cfield.h"

class CCave : public CField
{
public:
    CCave();

    virtual void execute() override;
    virtual std::string mapSymbol() const override;

private:
    void initDungeon();
};
