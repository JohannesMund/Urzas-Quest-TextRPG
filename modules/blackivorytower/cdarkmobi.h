#pragma once

#include <cenemy.h>

class CDarkMobi : public CEnemy
{
public:
    CDarkMobi(const bool isDeadly = true);

    virtual void spoilsOfWar() const override;
    virtual void battleAction(bool& endRound) override;
    virtual void postBattle() override;

protected:
    virtual std::string translatorModuleName() const override;
    const bool _isDeadly;
};
