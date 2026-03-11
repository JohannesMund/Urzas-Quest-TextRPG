#pragma once
#include "ctask.h"

class CCaveBossTask : public CTask
{
public:
    CCaveBossTask(bool* bossDefeated);

    virtual void execute() override;

    virtual bool isMovable() const override;

private:
    bool* _bossDefeated;
};
