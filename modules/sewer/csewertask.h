#pragma once

#include "ctask.h"

class CSewerTask : public CTask
{
public:
    CSewerTask();

    virtual void execute() override;

private:
    void executeDungeon();
};
