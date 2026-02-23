#pragma once

#include "cinventory.h"
#include "ctownmodule.h"

#include <string>

class CFishingFritz : public CTownModule
{
public:
    CFishingFritz();
    void execute() override;
    virtual CMenuAction townModuleNav(CMenu& menu) const override;

    nlohmann::json save() const override;
    virtual void load(const nlohmann::json& o) override;

protected:
    virtual std::string translatorModuleName() const override;
    virtual std::string translatorObjectName() const override;

private:
    void printHeader() const;

    bool isOpen() const;

    void ask();
    void checkFish();

    void getInformation() const;

    void sell() const;

    void enhance() const;

    bool isMakeRodActive() const;
    bool isMakeBoatActive() const;
    bool hasFish() const;
    int fishValue() const;

    void checkAndPrint(CInventory::EnhancableEquipmentList& equipmentList, CEquipment* item) const;

    bool _firstVisit = true;
};
