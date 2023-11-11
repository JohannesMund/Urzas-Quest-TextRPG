#include "csword.h"

CSword::CSword() : CEquipment()
{
    _hasBattleEffect = true;
    _hasBattleBuff = true;
}

std::string CSword::typeName() const
{
    return "sword";
}

std::function<bool(const CItem*)> CSword::equipmentTypeFilter() const
{
    return [](const CItem* item) -> bool { return dynamic_cast<const CSword*>(item) != nullptr; };
}
