#pragma once

#include "cfield.h"

class CCave : public CField
{
public:
    CCave();

    virtual void execute() override;
    virtual std::string mapSymbol() const override;

    virtual std::string bgColor() const override;
    virtual std::string fgColor() const override;

private:
    void initDungeon();
};
