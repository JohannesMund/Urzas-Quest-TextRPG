#pragma once

#include "cmenu.h"
#include "cnpc.h"

class CEnemy;
class CMobi : public CNpc
{
public:
    CMobi();

    virtual void interact() override;
    virtual void talk();

    virtual std::string name() const override;
    virtual std::string describe() const override;

    virtual CEnemy* enemy() const override;

    nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

protected:
    virtual std::string translatorModuleName() const override;

private:
    void giveFanta();

    void printHeader(const bool bFull = true) const override;
};
