#pragma once

#include "cequipment.h"

class CFishingRod : public CEquipment
{
public:
    CFishingRod();

    virtual std::string typeName() const override;
    static CItem::ItemFilter fishingRodFilter();
    virtual CItem::ItemFilter equipmentTypeFilter() const override;
    virtual unsigned int upgradeCost() const override;
};
