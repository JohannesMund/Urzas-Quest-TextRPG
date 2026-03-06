#pragma once

#include "cencounter.h"

class CNpc;
class CAppleTree : public CEncounter
{
public:
    CAppleTree(CNpc* kat);

    virtual void execute(const std::string_view& moduleName = {}) override;
    virtual unsigned int encounterChance(const EEncounterType& tp, const std::string_view& moduleName) const override;
    virtual std::string name() const override;
    virtual std::string moduleName() const override;

private:
    virtual std::string translatorObjectName() const override;

    const CNpc* _kat;
};