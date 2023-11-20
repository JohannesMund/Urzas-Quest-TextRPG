#pragma once

#include <cencounter.h>

class CCollectPartsEncounter : public CEncounter
{
public:
    CCollectPartsEncounter(const std::string_view& moduleName);

    virtual void execute(const std::string_view& moduleName = {}) override;
    virtual unsigned int encounterChance(const EEncounterType& tp, const std::string_view& moduleName) const override;
    virtual std::string name() const override;
    virtual std::string moduleName() const override;

private:
    void findFishingRodPart();
    void findBoatPart();

    const std::string _moduleName;
};
