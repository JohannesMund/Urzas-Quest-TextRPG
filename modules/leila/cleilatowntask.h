#pragma once

#include "ctask.h"
#include "menuaction.h"

class CLeilaTownTask : public CTask
{
public:
    CLeilaTownTask();

    virtual void execute() override;

    virtual Menu::MenuAction taskNav() const override;
};
