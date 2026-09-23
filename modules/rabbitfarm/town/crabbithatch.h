#pragma once

#include "ctownmodule.h"
#include "rabbitfarm/moduleressources.h"

#include <nlohmann/json_fwd.hpp>
#include <string>

class CKatNottingH;
class CRabbitMap;
class CRabbit;
class CRabbitHatch : public CTownModule
{
public:
    CRabbitHatch(CKatNottingH* kat, CRabbitMap* rabbits);

    void execute() override;
    virtual CMenuAction townModuleNav(CMenu& menu) const override;

    nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

protected:
    virtual std::string translatorModuleName() const override;
    virtual std::string translatorObjectName() const override;

private:
    void donate();
    void watch();
    void ask();
    void deliverRabbit();
    void watchOneRabbit();

    void registerEncounter();
    void makeRabbitOfTheMonth();

    CKatNottingH* _kat;
    CRabbitMap* _rabbits;

    CRabbit* _rabbitOfTheMonth = nullptr;
    int _rabbitOfTheMonthDate;
    bool _clearingEncounterRegistered = false;
};
