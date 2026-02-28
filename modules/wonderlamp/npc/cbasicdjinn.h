#pragma once

#include "cnpc.h"
#include "core.h"

#include <nlohmann/json_fwd.hpp>

class CBasicDjinn : public CNpc
{
public:
    static CBasicDjinn* loadFromJson(const nlohmann::json& json);

    CBasicDjinn(const Core::EGender gender);
    virtual ~CBasicDjinn(){};

    virtual void interact() override;
    virtual void talk() override = 0;

    virtual std::string name() const override = 0;
    virtual std::string describe() const override = 0;

    nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

protected:
    virtual std::string translatorModuleName() const override;
    virtual std::string colorize(const std::string_view& s) const = 0;

private:
    void printHeader(const bool bFull = true) const override = 0;
    void giftGem();
};