#pragma once

#include "cequipment.h"

class CEnemy;
class CSword : public CEquipment
{
public:
    CSword();
    virtual ~CSword()
    {
    }

    virtual void battleEffect(CEnemy* enemy) override = 0;
    virtual void battleBuff(CEnemy* enemy, bool& endRound) override = 0;
    virtual std::string typeName() const override;

    virtual std::function<bool(const CItem*)> equipmentTypeFilter() const override;
};
