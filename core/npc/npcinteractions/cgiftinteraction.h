#pragma once

#include "citem.h"
#include "cnpcinteraction.h"
#include "ressources.h"

class CGiftInteraction : public CNpcInteraction
{
public:
    CGiftInteraction(CNpc* npc, CItem::ItemFilter itemFilter);

    virtual void executeInteraction() override;
    virtual bool interactionAvailable() const override;

protected:
    virtual void makeNav(CMenu& menu) override;

private:
    const CItem::ItemFilter _itemFilter;
};