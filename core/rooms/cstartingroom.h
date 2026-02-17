#pragma once

#include <cfield.h>

class CStartingRoom : public CField
{
public:
    CStartingRoom();
    virtual void execute() override;

protected:
    virtual std::string translatorModuleName() const override;

private:
    virtual char getMapSymbol() const override;
};
