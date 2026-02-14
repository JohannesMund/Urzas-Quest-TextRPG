#pragma once

#include "cencounter.h"

class CSewerBattleEncounter : public CEncounter
{
public:
    CSewerBattleEncounter();

    virtual void execute(const std::string_view& moduleName = {}) override;
    virtual unsigned int encounterChance(const EEncounterType& tp,
                                         const std::string_view& moduleName = {}) const override;
    virtual std::string name() const override;
    virtual std::string moduleName() const override;

protected:
    virtual std::string translatorModuleName() const override;
};
