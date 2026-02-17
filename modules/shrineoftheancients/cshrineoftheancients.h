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

protected:
    virtual std::string translatorModuleName() const override;

    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

private:
    Module::EGameStage _seenDuringPhase = Module::EGameStage::eNone;

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
