#pragma once

#include "ctownmodule.h"

class CBlackSmith : public CTownModule
{
public:
    CBlackSmith();
    virtual void execute() override;

private:
    void enhanceItem();
};
