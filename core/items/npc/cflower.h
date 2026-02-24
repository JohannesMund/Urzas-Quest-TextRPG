#pragma once

#include "citem.h"
#include "ressources.h"

#include <nlohmann/json.hpp>

class CFlower : public CItem
{
public:
    CFlower();

    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json& o) override;

protected:
    virtual std::string translatorModuleName() const override;

private:
    Ressources::Items::EFlower _flowerType;
};
