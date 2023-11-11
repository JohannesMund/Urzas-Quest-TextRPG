#pragma once

#include <citem.h>

class CRatFarmTurnip : public CItem
{
public:
    enum class TurnipSize
    {
        S,
        M,
        L
    };

    CRatFarmTurnip(const TurnipSize& size = TurnipSize::M);
    virtual void useFromInventory() override;
    virtual void useFromBattle(CEnemy*) override;

private:
    void use();
    TurnipSize _size;
};
