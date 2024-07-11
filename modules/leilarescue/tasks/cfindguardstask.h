#pragma once

#include "ctask.h"

class CFindGuardsTask : public CTask
{

public:
    CFindGuardsTask(const unsigned int number = 0);
    virtual void execute() override;

    void finishTask();

private:
    void findFirstGuard();
    void fightCannibalHorde();
    void rescueGuardFromMafia();
    void fightBossMonster();
    void collectStuff();

    const unsigned int _number = 0;
    static constexpr unsigned int _maxNumber = 4;

    const unsigned int _mafiaStartingMoney = 10000;
    const unsigned int _maxMafiaMoney = 25000;
    const unsigned int _mafiaIntrest = 13;
    unsigned int _mafiaMoney = _mafiaStartingMoney;

    std::string nameOfCurrentGuard() const;

    bool _stuffCollectionStarted = false;
};