#pragma once

#include "cinventory.h"
#include "ctranslatable.h"

#include <string>

class CFishingFritz : public CTranslatable
{
public:
    CFishingFritz();

    void execute();

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
