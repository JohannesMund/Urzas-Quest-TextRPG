#pragma once

#include "cnpcinteraction.h"
#include "ressources.h"

class CFlowerInteraction : public CNpcInteraction
{
public:
    CFlowerInteraction(CNpc* npc);

    virtual void executeInteraction() override;
    virtual bool interactionAvailable() const override;

    nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

protected:
    virtual void makeNav(CMenu& menu) override;

private:
    Ressources::Items::EFlower _favoriteFlower;
    Ressources::Items::EFlower _leastFavoriteFlower;
};