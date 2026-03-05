#pragma once
#include "cmenu.h"
#include "cnpc.h"

class CKatNottingH : public CNpc
{
public:
    CKatNottingH();

    virtual void interact() override;
    virtual void talk() override;

    virtual std::string name() const override;
    virtual std::string describe() const override;

    nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

protected:
    virtual std::string translatorModuleName() const override;

private:
    void printHeader(const bool bFull = true) const override;
};
