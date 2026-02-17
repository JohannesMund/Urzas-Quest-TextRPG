#pragma once

#include "ctranslatable.h"

class CFishingRod;
class CEquipment;
class CGoFishing : public CTranslatable
{
public:
    CGoFishing();

    void execute();

protected:
    virtual std::string translatorModuleName() const override;
    virtual std::string translatorObjectName() const override;

private:
    void init();
    void printItemLevels();
    void catchAFish();
    CEquipment* _fishingRod = nullptr;
    CEquipment* _boat = nullptr;
};
