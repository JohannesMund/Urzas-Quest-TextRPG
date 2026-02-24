#pragma once

#include "ckatnottingh.h"
#include "crabbitmap.h"
#include "croom.h"
#include "rabbitfarm/town/crabbithatch.h"
#include "rabbitfarm/town/cslasher.h"

class CRabbitFarm : public CRoom
{

public:
    CRabbitFarm();

    virtual void execute() override;

    virtual std::string bgColor() const override;
    virtual std::string fgColor() const override;

protected:
    virtual std::string translatorModuleName() const override;

    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

private:
    virtual char getMapSymbol() const override;
    virtual void printHeader() const;

    CKatNottingH _kat;
    CSlasher _slasher;
    CRabbitHatch _rabbitHatch;

    CRabbitMap _rabbits;
};