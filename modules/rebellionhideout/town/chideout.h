#pragma once

#include "cgamemanagement.h"
#include "ctownmodule.h"
#include "rebellionhideout/moduleressources.h"
#include "rebellionhideout/npc/cguardnpc.h"

#include <string>

class CHideout : public CTownModule
{
public:
    CHideout();
    void execute() override;
    virtual CMenuAction townModuleNav(CMenu& menu) const override;

protected:
    virtual std::string translatorModuleName() const override;
    virtual std::string translatorObjectName() const override;

private:
    void talkToRebellion();

    CGuardNpc _piefke;
};
