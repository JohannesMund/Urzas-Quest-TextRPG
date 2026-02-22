#pragma once

#include "ckatnothingh.h"
#include "croom.h"
#include "town/crabbithatch.h"
#include "town/cslasher.h"

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

    CKatNothingH _kat;
    CSlasher _slasher;
    CRabbitHatch _rabbitHatch;
};