#pragma once

#include <ctask.h>

class CTattooParlor : public CTask
{
public:
    CTattooParlor();

    virtual void execute() override;

    virtual char mapSymbol() const override;

protected:
    virtual std::string translatorModuleName() const override;

private:
    void tattooParlor();
    void askForRemoval();
    void coverUp();
    void printTattoos();
};
