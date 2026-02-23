#pragma once

#include "ctownmodule.h"

class CFishingRod;
class CEquipment;
class CGoFishing : public CTownModule
{
public:
    CGoFishing();

    void execute() override;
    virtual CMenuAction townModuleNav(CMenu& menu) const override;

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
