#pragma once

#include "ctownmodule.h"

class CFarm : public CTownModule
{
public:
    CFarm();

    virtual void execute() override;
    virtual CMenuAction townModuleNav(CMenu& menu) const override;

private:
    void train();

    int getTrainingCost() const;
};
