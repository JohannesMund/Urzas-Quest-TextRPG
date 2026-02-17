#pragma once
#include "cenemy.h"

class CLivingChest : public CEnemy
{
public:
    CLivingChest();

    virtual void spoilsOfWar() const override;
    virtual void battleAction(bool& endRound) override;

protected:
    virtual std::string translatorModuleName() const override;
};
