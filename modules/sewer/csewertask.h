#pragma once

#include "ctask.h"
#include "menuaction.h"

class CSewerTask : public CTask
{
public:
    CSewerTask();

    virtual void execute() override;

    virtual Menu::MenuAction taskNav() const override;

private:
    void executeDungeon();
};
