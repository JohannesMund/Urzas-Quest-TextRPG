#pragma once
#include "cmobenemy.h"

class CLunatic : public CMobEnemy
{
public:
    CLunatic();

    virtual unsigned int damage() const override;

    virtual int shieldingAction(const int damage) const override;

private:
    enum class ELunaticType
    {
        eWarrior,
        eDefender,
        eMage
    };
    ELunaticType _type;
};