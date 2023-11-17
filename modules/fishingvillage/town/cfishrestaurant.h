#pragma once

#include "fishingvillage/moduleressources.h"

#include <string>

class CFishRestaurant
{
public:
    CFishRestaurant();
    void execute();

private:
    void makeDishOfTheDay();
    unsigned int priceOfTheDay() const;
    void eat() const;

    std::string _dishOfTheDay;
    FishingVillageRessources::EFishLevel _dishOfTheDayLevel;
};
