#include "cflower.h"

CFlower::CFlower() : CItem(TagNames::Item::Npc::flower)
{
    _flowerType = Ressources::Items::getRandomFlowerType();
    _name = Ressources::Items::flower2String(_flowerType);
    _value = Ressources::Items::flower2Value(_flowerType);
    _isSellable = true;
}

nlohmann::json CFlower::save() const
{
    nlohmann::json o = CItem::save();
    o["flowerType"] = _flowerType;
    return o;
}

void CFlower::load(const nlohmann::json& o)
{
    CItem::load(o);
    _flowerType = o["flowerType"];
}

std::string CFlower::translatorModuleName() const
{
    return std::string();
}
