#pragma once

#include "cequipment.h"

class CArmor : public CEquipment
{
public:
    CArmor();

    virtual void battleEffect(CEnemy* enemy) override = 0;
    virtual int shield(const unsigned int i) override = 0;
    virtual std::string typeName() const override;

    virtual std::function<bool(const CItem*)> equipmentTypeFilter() const override;
};
