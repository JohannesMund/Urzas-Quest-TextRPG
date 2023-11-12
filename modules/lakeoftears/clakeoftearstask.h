#pragma once

#include <ctask.h>

class CLakeOfTearsTask : public CTask
{
public:
    CLakeOfTearsTask(const unsigned int steps = 0);

    virtual void execute() override;

private:
    enum class EEnemy
    {
        eFrog,
        eHornet,
        eSnake,
        eSnail
    };

    const unsigned int _steps = 0;

    void battle(const EEnemy enemy);
};
