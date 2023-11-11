#pragma once

#include "carmor.h"

class CJunkArmor : public CArmor
{
public:
    CJunkArmor();

    virtual std::string name() const override;
    virtual void battleEffect(CEnemy* enemy) override;
    virtual int shield(const unsigned int i) override;
};
