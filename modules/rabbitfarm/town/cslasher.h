#pragma once

#include "ctownmodule.h"
#include "rabbitfarm/moduleressources.h"

#include <string>

class CKatNothingH;
class CRabbitMap;
class CSlasher : public CTownModule
{
public:
    CSlasher(CKatNothingH* kat, CRabbitMap* rabbits);
    void execute() override;
    virtual CMenuAction townModuleNav(CMenu& menu) const override;

protected:
    virtual std::string translatorModuleName() const override;
    virtual std::string translatorObjectName() const override;

private:
    void eat();
    void deliverRabbit();
    void ask();

    void makeDishOfTheDay();

    CKatNothingH* _kat;
    CRabbitMap* _rabbits;
    std::string _dishOfTheDay;
};
