#pragma once

#include "ctownmodule.h"

class CBlackSmith : public CTownModule
{
public:
    CBlackSmith();
    virtual void execute() override;

    virtual CMenuAction townModuleNav(CMenu& menu) const override;

private:
    void enhanceItem();
};
