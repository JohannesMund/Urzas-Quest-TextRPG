#pragma once

#include "ctownmodule.h"

class CTavern : public CTownModule
{
public:
    CTavern();

    virtual void execute() override;
    virtual CMenuAction townModuleNav(CMenu& menu) const override;

private:
    void bountyHunt();
};
