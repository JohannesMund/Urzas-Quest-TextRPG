#include "crabbit.h"

#include "rabbitfarm/moduleressources.h"

CRabbit::CRabbit(const unsigned int uniqueId) : CItem(TagNames::RabbitFarm::rabbit), _uniqueId(uniqueId)
{
    _name = RabbitFarm::makeRabbitName();
    _description = tr("One particularly unique, rare Rabbit.");

    _isConsumable = false;
    _isUsableFromInventory = false;
    _isUsableFromBattle = false;
    _isSellable = false;
}

CItem::ItemFilter CRabbit::rabbitFilter()
{
    return [](const CItem* item) { return dynamic_cast<const CRabbit*>(item) != nullptr; };
}

unsigned int CRabbit::uniqueId() const
{
    return _uniqueId;
}

std::string CRabbit::translatorModuleName() const
{
    return RabbitFarm::moduleName();
}
