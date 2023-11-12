#pragma once

#include "cgameprogression.h"

#include <cfield.h>

class CShrineOfTheAncients : public CField
{
public:
    CShrineOfTheAncients();

    virtual void execute() override;
    virtual std::string mapSymbol() const override;

private:
    CGameProgression::EGameStage _seenDuringPhase = CGameProgression::EGameStage::eNone;

    void visit();
    void firstVisit();

    void firstVisitStart();
    void firstVisitSeenBard();
    void firstVisitProvenAsHero();

    void stats() const;

    std::string ancientShrine() const;
};
