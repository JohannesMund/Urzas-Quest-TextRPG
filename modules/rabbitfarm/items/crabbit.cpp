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

void CRabbit::roast()
{
    _isRoasted = true;
    _description = tr("A delicious rabbit roast, made from a particularly unique, rare rabbit.");
}

bool CRabbit::isRoasted() const
{
    return _isRoasted;
}

std::string CRabbit::translatorModuleName() const
{
    return RabbitFarm::moduleName();
}

nlohmann::json CRabbit::save() const
{
    auto o = CItem::save();
    o["isRoasted"] = _isRoasted;
    o["uniqueId"] = _uniqueId;

    return o;
}

void CRabbit::load(const nlohmann::json& json)
{
    CItem::load(json);
    _isRoasted = json["isRoasted"];
    _uniqueId = json["uniqueId"];
}
