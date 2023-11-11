#include "carmor.h"

CArmor::CArmor() : CEquipment()
{
    _hasBattleEffect = true;
    _hasShieldingAction = true;
}

std::string CArmor::typeName() const
{
    return "armor";
}

std::function<bool(const CItem*)> CArmor::equipmentTypeFilter() const
{
    return [](const CItem* item) -> bool { return dynamic_cast<const CArmor*>(item) != nullptr; };
}
