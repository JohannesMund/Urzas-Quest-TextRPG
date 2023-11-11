#pragma once
#include <citem.h>

class CEnemy;
class CHealingPotion : public CItem
{
public:
    enum class PotionSize
    {
        S,
        M,
        L,
        XL
    };

    CHealingPotion(const PotionSize& size = PotionSize::M);
    virtual void useFromInventory() override;
    virtual void useFromBattle(CEnemy*) override;

private:
    void use();

    PotionSize _size;
};
