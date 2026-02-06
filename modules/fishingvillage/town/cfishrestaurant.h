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
    int priceOfTheDay() const;
    void eat() const;

    std::string _dishOfTheDay;
    FishingVillage::EFishLevel _dishOfTheDayLevel;
};
