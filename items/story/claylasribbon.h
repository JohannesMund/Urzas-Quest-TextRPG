#pragma once

#include "citem.h"

class CLaylasRibbon : public CItem
{
public:
    CLaylasRibbon();

    virtual void battleEffect(CEnemy* enemy) override;
    virtual int shield(const unsigned int i) override;
};
