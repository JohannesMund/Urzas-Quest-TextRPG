#pragma once

#include <cfield.h>

class CFishingVillage : public CField
{
public:
    CFishingVillage();

    virtual void execute() override;
    virtual std::string mapSymbol() const override;

    virtual std::string bgColor() const override;
    virtual std::string fgColor() const override;

private:
    void printHeader();
};
