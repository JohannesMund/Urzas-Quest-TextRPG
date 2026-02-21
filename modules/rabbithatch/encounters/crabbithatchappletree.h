#pragma once

#include "cencounter.h"

class CKatNothingH;
class CRabbitHatchAppleTree : public CEncounter
{
public:
    CRabbitHatchAppleTree(CKatNothingH* kat);

    virtual void execute(const std::string_view& moduleName = {}) override;
    virtual unsigned int encounterChance(const EEncounterType& tp, const std::string_view& moduleName) const override;
    virtual std::string name() const override;
    virtual std::string moduleName() const override;

private:
    virtual std::string translatorModuleName() const override;
    const CKatNothingH* _kat;
};