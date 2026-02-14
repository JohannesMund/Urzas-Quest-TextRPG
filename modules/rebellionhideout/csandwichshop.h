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

protected:
    virtual std::string translatorModuleName() const override;

    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

private:
    void printHeader();

    void showSandwichOfTheDay();
    void eatSandwichOfTheDay();

    void checkForShaggysSandwich();
    void checkForSoldSandwiches();
    bool seenRebellionHideoutHint();

    void revolutionaryThoughts();

    void deliverIngredients();
    void makeASandwich();
    void observe();
    void talkToRebellion();

    int countIngredients();

    virtual char getMapSymbol() const override;

    void replaceSandwichOfTheDay();

    void registerItemGenerators();

    unsigned long _turns = 0;
    bool _playerOwnsShop = false;
    bool _playerDiscoveredHideout = false;
    int _goldAvailable = 0;

    bool _itemGeneratorsRegistered = false;

    std::vector<CSandwich*> _sandwiches;
    std::map<CSandwich::EIngredients, int> _ingredientStore;
};
