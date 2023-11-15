#pragma once

#include "ctask.h"

class CLaylaTownTask : public CTask
{
public:
    CLaylaTownTask();

    virtual void execute() override;

    virtual std::string taskNav() const override;
};
