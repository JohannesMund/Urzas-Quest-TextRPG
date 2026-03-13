#pragma once

#include <ctask.h>

class CLeilaTask : public CTask
{
public:
    CLeilaTask();

    virtual void execute() override;

protected:
    virtual std::string translatorModuleName() const override;
};
