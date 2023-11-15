#pragma once

#include "cequipment.h"
#include "ressources.h"

class CEnemy;
class CWeapon : public CEquipment
{
public:
    CWeapon(const Ressources::Items::EQuality quality);

    virtual void battleEffect(CEnemy* enemy) override;
    virtual void battleBuff(CEnemy* enemy, bool& endRound) override;
    virtual std::string typeName() const override;

    virtual std::function<bool(const CItem*)> equipmentTypeFilter() const override;

private:
    virtual unsigned int extraDamage() const;
};
