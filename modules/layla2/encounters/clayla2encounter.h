#pragma once

#include "cencounter.h"

class CLayla2Encounter : public CEncounter
{
public:
    CLayla2Encounter();

    virtual void execute(const std::string_view& moduleName = {}) override;
    virtual unsigned int encounterChance(const EEncounterType& tp, const std::string_view& moduleName) const override;
    virtual std::string name() const override;
    virtual std::string moduleName() const override;

};
