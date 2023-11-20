#pragma once

#include "cmap.h"
#include "croom.h"

class CField : public CRoom
{
public:
    CField();

    virtual std::string mapSymbol() const override;

    virtual std::string fgColor() const override;
    virtual std::string bgColor() const override;

    static CMap::RoomFilter fieldFilter();
};
