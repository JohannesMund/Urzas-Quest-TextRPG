#pragma once

#include "ctask.h"

class CFindGuardsTask : public CTask
{

public:
    CFindGuardsTask(const unsigned int number = 0);
    virtual void execute() override;

    void finishTask();

private:
    void findFirstGuard();
    void fightCannibalHorde();
    void rescueGuardFromMafia();
    unsigned int _number = 0;

    const unsigned int _maxNumber = 5;
};