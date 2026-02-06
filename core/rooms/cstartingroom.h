#pragma once

#include <cfield.h>

class CStartingRoom : public CField
{
public:
    CStartingRoom();
    virtual void execute() override;

private:
    virtual char getMapSymbol() const override;
};
