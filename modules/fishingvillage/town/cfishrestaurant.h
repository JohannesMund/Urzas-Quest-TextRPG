#pragma once

#include "ctranslatable.h"
#include "fishingvillage/moduleressources.h"

#include <string>

class CFishRestaurant : public CTranslatable
{
public:
    CFishRestaurant();
    void execute();

protected:
    virtual std::string translatorModuleName() const override;
    virtual std::string translatorObjectName() const override;

private:
    void makeDishOfTheDay();
    int priceOfTheDay() const;
    void eat() const;

    std::string _dishOfTheDay;
    FishingVillage::EFishLevel _dishOfTheDayLevel;
};
