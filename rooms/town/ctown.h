#pragma once

#include "cblacksmith.h"
#include "cchurch.h"
#include "cfarm.h"
#include "cinventory.h"
#include "cmap.h"
#include "croom.h"
#include "cshop.h"
#include "ctavern.h"

#include <string>

class CItem;
class CTown : public CRoom
{
public:
    CTown();

    virtual void execute() override;
#
    virtual std::string bgColor() const override;
    virtual std::string fgColor() const override;

    std::string name() const;

    static CMap::RoomFilter townFilter();

private:
    std::string _name;

    virtual char getMapSymbol() const override;

    CShop _shop;
    CChurch _church;
    CBlackSmith _blackSmith;
    CFarm _farm;
    CTavern _tavern;
};
