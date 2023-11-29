#pragma once

#include "ctown.h"

class CCapital : public CTown
{
public:
    CCapital();

    virtual void execute() override;

    virtual std::string bgColor() const override;
    virtual std::string fgColor() const override;

    static CMap::RoomFilter capitalFilter();

private:
    virtual char getMapSymbol() const override;

    bool _open = false;
};
