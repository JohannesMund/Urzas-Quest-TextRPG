#pragma once
#include "ctownmodule.h"

#include <string>

class CChurch : public CTownModule
{
public:
    CChurch();
    virtual void execute() override;
};
