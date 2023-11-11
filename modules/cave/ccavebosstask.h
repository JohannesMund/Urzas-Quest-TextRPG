#pragma once
#include <ctask.h>

class CCaveBossTask : public CTask
{
public:
    CCaveBossTask(bool* bossDefeated);

    virtual void execute() override;

private:
    bool* _bossDefeated;
};
