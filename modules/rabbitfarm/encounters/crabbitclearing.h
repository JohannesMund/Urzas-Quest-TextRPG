#pragma once

#include "cencounter.h"
#include "cmenuaction.h"

class CKatNothingH;
class CRabbitMap;
class CRabbitClearing : public CEncounter
{
public:
    CRabbitClearing(CKatNothingH* kat, const CRabbitMap* rabbits);

    virtual void execute(const std::string_view& moduleName = {}) override;
    virtual unsigned int encounterChance(const EEncounterType& tp, const std::string_view& moduleName) const override;
    virtual std::string name() const override;
    virtual std::string moduleName() const override;

private:
    virtual std::string translatorModuleName() const override;
    virtual std::string translatorObjectName() const override;

    CKatNothingH* _kat;
    const CRabbitMap* _rabbits;
};