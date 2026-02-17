#pragma once

#include "cmap.h"
#include "croom.h"

class CField : public CRoom
{
public:
    CField(const std::string_view& objectName = TagNames::Room::field);

    virtual std::string fgColor() const override;
    virtual std::string bgColor() const override;

    static CMap::RoomFilter fieldFilter();

protected:
    virtual std::string translatorModuleName() const override;

    virtual char getMapSymbol() const override;
};
