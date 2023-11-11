#pragma once

#include "cencounter.h"

class CMysteriousChest : public CEncounter
{
public:
    CMysteriousChest();

    virtual void execute(const std::string_view& moduleName = {}) override;
    virtual unsigned int encounterChance(const EEncounterType& tp, const std::string_view& moduleName) const override;
    virtual std::string name() const override;
};
