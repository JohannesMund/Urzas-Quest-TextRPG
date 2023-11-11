#pragma once

#include "citem.h"

class CEnemy;
class CBomb : public CItem
{
public:
    enum class BombSize
    {
        S,
        M,
        L,
        XL
    };

    CBomb(const BombSize& size = BombSize::M);

    virtual void useFromBattle(CEnemy* enemy) override;

private:
    BombSize _size;
};
