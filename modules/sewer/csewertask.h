#pragma once

#include "ctask.h"

class CSewerTask : public CTask
{
public:
    CSewerTask();

    virtual void execute() override;

    virtual std::string taskNav() const override;

private:
    void executeDungeon();
};
