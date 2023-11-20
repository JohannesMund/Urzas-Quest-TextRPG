#pragma once

#include <ctask.h>

class COpenCaveTask : public CTask
{
public:
    COpenCaveTask();

    virtual void execute() override;
    virtual std::string moduleName() const override;
};
