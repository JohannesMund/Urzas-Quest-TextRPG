#pragma once

#include "cenemy.h"

class CBountyEnemy : public CEnemy
{
public:
    CBountyEnemy(const std::string& name);

    virtual void spoilsOfWar() const override;
    virtual void battleAction(bool& endRound) override;

protected:
    virtual std::string translatorModuleName() const override;
};
