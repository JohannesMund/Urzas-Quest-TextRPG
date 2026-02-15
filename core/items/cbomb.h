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

    virtual nlohmann::json save() const override;

protected:
    virtual std::string translatorModuleName() const override;

private:
    BombSize _size;
};
