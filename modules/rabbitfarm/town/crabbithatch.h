#pragma once

#include "ctownmodule.h"
#include "rabbitfarm/moduleressources.h"

#include <string>

class CKatNothingH;

class CRabbitMap;
class CRabbitHatch : public CTownModule
{
public:
    CRabbitHatch(CKatNothingH* kat, CRabbitMap* rabbits);

    void execute() override;
    virtual CMenuAction townModuleNav(CMenu& menu) const override;

protected:
    virtual std::string translatorModuleName() const override;
    virtual std::string translatorObjectName() const override;

private:
    void donate();
    void watch();
    void ask();
    void deliverRabbit();
    void watchOneRabbit();

    void makeRabbitOfTheDay();

    CKatNothingH* _kat;
    CRabbitMap* _rabbits;

    std::string _rabbitOfTheDay;
};
