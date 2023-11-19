#pragma once

#include "cmap.h"
#include "croom.h"

class CFishingVillage : public CRoom
{
public:
    CFishingVillage();

    virtual void execute() override;
    virtual std::string mapSymbol() const override;

    virtual std::string bgColor() const override;
    virtual std::string fgColor() const override;

    static CMap::RoomFilter fishingVillageFilter();

private:
    void printHeader();
};
