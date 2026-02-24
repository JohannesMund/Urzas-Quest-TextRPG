#pragma once

#include "citem.h"

class CUrzasGlasses : public CItem
{
public:
    CUrzasGlasses();
    virtual void battleBuff(CEnemy* enemy, bool& endRound) override;

protected:
    virtual std::string translatorModuleName() const override;
};
