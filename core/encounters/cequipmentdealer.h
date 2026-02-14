#pragma once

#include "cencounter.h"

class CEquipmentDealer : public CEncounter
{
public:
    CEquipmentDealer();

    virtual void execute(const std::string_view& moduleName = {}) override;
    virtual unsigned int encounterChance(const EEncounterType& tp, const std::string_view& moduleName) const override;
    virtual std::string name() const override;

    virtual bool canBeExecuted(const EEncounterType& tp) const override;

protected:
    virtual std::string translatorModuleName() const override;
};
