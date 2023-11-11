#include "cshield.h"

CShield::CShield() : CEquipment()
{
    _hasBattleEffect = true;
    _hasBattleBuff = true;
}

std::string CShield::typeName() const
{
    return "shield";
}

std::function<bool(const CItem*)> CShield::equipmentTypeFilter() const
{
    return [](const CItem* item) -> bool { return dynamic_cast<const CShield*>(item) != nullptr; };
}
