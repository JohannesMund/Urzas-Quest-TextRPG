#pragma once

#include <ctask.h>

class CLaylaTask : public CTask
{
public:
    CLaylaTask();

    virtual void execute() override;

private:
    void battle();
};
