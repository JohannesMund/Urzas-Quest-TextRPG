#pragma once

#include "ctask.h"

class CRatFarmTask : public CTask
{
public:
    CRatFarmTask();

    virtual void execute() override;

private:
    void battle();
};
