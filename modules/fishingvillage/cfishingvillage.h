#pragma once

#include "cmap.h"
#include "croom.h"
#include "fishingvillage/town/cfishingfritz.h"
#include "fishingvillage/town/cfishrestaurant.h"
#include "fishingvillage/town/cgofishing.h"

class CFishingVillage : public CRoom
{
public:
    CFishingVillage();

    virtual void execute() override;

    virtual std::string bgColor() const override;
    virtual std::string fgColor() const override;

    static CMap::RoomFilter fishingVillageFilter();

private:
    virtual std::string translatorModuleName() const override;

    void printHeader();

    virtual char getMapSymbol() const override;

    CFishingFritz _fishingFritz;
    CFishRestaurant _fishRestaurant;
    CGoFishing _goFishing;
};
