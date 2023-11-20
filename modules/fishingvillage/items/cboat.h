#pragma once

#include "cequipment.h"

class CBoat : public CEquipment
{
public:
    CBoat();

    virtual std::string typeName() const override;
    static CItem::ItemFilter boatFilter();
    virtual CItem::ItemFilter equipmentTypeFilter() const override;
    virtual unsigned int upgradeCost() const override;
};
