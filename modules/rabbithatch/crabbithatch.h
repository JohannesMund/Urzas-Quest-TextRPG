#pragma once

#include "ckatnothingh.h"
#include "croom.h"

class CRabbitHatch : public CRoom
{

public:
    CRabbitHatch();

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
};