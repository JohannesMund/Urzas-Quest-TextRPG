#pragma once

#include <ctask.h>

class CLakeOfTearsTask : public CTask
{
public:
    CLakeOfTearsTask(const unsigned int steps = 0);

    virtual void execute() override;

protected:
    virtual nlohmann::json save() const override;
    virtual bool load(const nlohmann::json&) override;

private:
    enum class EEnemy
    {
        eFrog,
        eHornet,
        eSnake,
        eSnail
    };

    unsigned int _steps = 0;

    void battle(const EEnemy enemy);
};
