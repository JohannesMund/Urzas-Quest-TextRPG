#pragma once

#include "ctask.h"

class CLeilaTownTask : public CTask
{
public:
    CLeilaTownTask();

    virtual void execute() override;

    virtual std::string taskNav() const override;
};
