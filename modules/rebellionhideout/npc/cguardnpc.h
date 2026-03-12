#pragma once

#include "cmenu.h"
#include "cnpc.h"

class CEnemy;
class CGuardNpc : public CNpc
{
public:
    CGuardNpc(const std::string_view& name);

    virtual void interact() override;
    virtual void talk();

    virtual std::string name() const override;
    virtual std::string describe() const override;

    nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

protected:
    virtual std::string translatorModuleName() const override;

private:
    void printHeader(const bool bFull = true) const override;
    std::string _name;
};
