#pragma once

#include "croom.h"
#include "csandwich.h"

#include <map>
#include <vector>

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

    void checkForShaggysSandwich();
    void deliverIngredients();
    void makeASandwich();

    void sellSandwiches();

    int countIngredients();

    virtual char getMapSymbol() const override;

    void replaceSandwichOfTheDay();

    unsigned long _turns = 0;
    bool _playerOwnsShop = false;
    bool _playerDiscoveredHideout = false;
    int _goldAvailable = 0;

    std::vector<CSandwich*> _sandwiches;
    std::map<CSandwich::EIngredients, int> _ingredientStore;
};
