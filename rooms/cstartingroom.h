#pragma once

#include <cfield.h>

class CStartingRoom : public CField
{
public:
    CStartingRoom();

    virtual void execute() override;
    virtual std::string mapSymbol() const override;
};
