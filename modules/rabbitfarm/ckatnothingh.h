#pragma once
#include "cnpc.h"

class CKatNothingH : public CNpc
{
public:
    CKatNothingH();

    virtual void interact() override;
    virtual void talk() override;

    virtual std::string name() const override;
    virtual std::string describe() const override;

    nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

protected:
    virtual std::string translatorModuleName() const override;

private:
    void registerAppleEncounter();
    void giveApple();
    bool _appleEncounterRegistered = false;
    void printHeader(const bool bFull = true) const override;
};
