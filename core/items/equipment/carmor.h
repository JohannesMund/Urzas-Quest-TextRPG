#pragma once

#include "cequipment.h"

class CArmor : public CEquipment
{
public:
    CArmor(const Ressources::Items::EQuality quality);

    virtual void battleEffect(CEnemy* enemy) override;
    virtual int shield(const unsigned int i) override;
    virtual std::string typeName() const override;

    virtual ItemFilter equipmentTypeFilter() const override;

private:
    virtual unsigned int shieldAmount() const;
};
