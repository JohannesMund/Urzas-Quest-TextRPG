#pragma once

#include "cgameprogression.h"
#include "croom.h"
#include "ressources.h"

class CShrineOfTheAncients : public CRoom
{
public:
    CShrineOfTheAncients();

    virtual void execute() override;

    virtual std::string fgColor() const override;
    virtual std::string bgColor() const override;

private:
    CGameProgression::EGameStage _seenDuringPhase = CGameProgression::EGameStage::eNone;

    void visit();
    void firstVisit();

    void firstVisitStart();
    void firstVisitSeenBard();
    void firstVisitProvenAsHero();
    void firstVisitLearnedAboutCult();

    void stats() const;

    virtual char getMapSymbol() const override;

    std::string ancientShrine() const;
};
