#pragma once

#include "ctownmodule.h"

class CFarm : public CTownModule
{
public:
    CFarm();

    virtual void execute() override;

private:
    void train();

    int getTrainingCost() const;
};
