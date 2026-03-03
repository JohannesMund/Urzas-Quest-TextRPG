#pragma once

#include "cbasicdjinn.h"

class CGenie : public CBasicDjinn
{
public:
    CGenie();

    virtual void talk() override;

    virtual std::string name() const override;
    virtual std::string describe() const override;

protected:
    virtual std::string colorize(const std::string_view& s) const override;
};