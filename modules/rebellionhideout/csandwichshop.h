#pragma once

#include "croom.h"

#include <vector>

class CSandwich;
class CSandwichShop : public CRoom
{
public:
    CSandwichShop();

    virtual void execute() override;

    virtual std::string bgColor() const override;
    virtual std::string fgColor() const override;

    static CMap::RoomFilter sandwichShopFilter();

private:
    void printHeader();

    void showSandwichOfTheDay();
    void eatSandwichOfTheDay();

    void checkSandwich();

    void sellSandwiches();

    virtual char getMapSymbol() const override;

    void replaceSandwichOfTheDay();

    std::vector<CSandwich*> _sandwiches;
    unsigned long _turns = 0;

    bool _playerOwnsShop = false;
    bool _playerDiscoveredHideout = false;
};
