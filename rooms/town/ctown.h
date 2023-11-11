#pragma once

#include "cblacksmith.h"
#include "cchurch.h"
#include "cfarm.h"
#include "cinventory.h"
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
    virtual std::string mapSymbol() const override;

    std::string name() const;

private:
    std::string _name;

    CShop _shop;
    CChurch _church;
    CBlackSmith _blackSmith;
    CFarm _farm;
    CTavern _tavern;
};
