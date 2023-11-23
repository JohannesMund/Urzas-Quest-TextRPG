#ifndef CURZASGLASSES_H
#define CURZASGLASSES_H

#include "citem.h"

class CUrzasGlasses : public CItem
{
public:
    CUrzasGlasses();
    virtual void battleBuff(CEnemy* enemy, bool& endRound) override;
};

#endif // CURZASGLASSES_H
