#pragma once

#include "cbasicdjinn.h"

class CGenie : public CBasicDjinn
{
public:
    CGenie();

    virtual std::string name() const override;
    virtual std::string describe() const override;

    virtual void load(const nlohmann::json& json) override;

protected:
    virtual std::string colorize(const std::string_view& s) const override;
};