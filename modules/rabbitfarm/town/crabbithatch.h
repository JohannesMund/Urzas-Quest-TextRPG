#pragma once

#include "ctownmodule.h"
#include "rabbitfarm/moduleressources.h"

#include <string>

class CKatNothingH;
class CRabbit;
class CRabbitHatch : public CTownModule
{
public:
    CRabbitHatch(CKatNothingH* kat);
    void execute() override;
    virtual CMenuAction townModuleNav(CMenu& menu) const override;

protected:
    virtual std::string translatorModuleName() const override;
    virtual std::string translatorObjectName() const override;

private:
    void donate();
    void watch();
    void talk();
    void deliverRabbit();

    CKatNothingH* _kat;
    std::map<int, CRabbit*> _rabbits;
};
