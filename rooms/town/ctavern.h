#pragma once

#include "ctownmodule.h"

class CTavern : public CTownModule
{
public:
    CTavern();

    virtual void execute() override;

private:
    void bountyHunt();
};
