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

protected:
    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json&) override;

private:
    void use();
    TurnipSize _size;
};
