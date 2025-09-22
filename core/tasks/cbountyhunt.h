#pragma once

#include "ctask.h"

#include <string>
class CBountyHunt : public CTask
{
public:
    CBountyHunt(const std::string& name, const unsigned int reward);
    virtual ~CBountyHunt();

    static bool isHuntActive();

    virtual void execute() override;

    std::string name() const;

protected:
    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json&) override;

private:
    std::string _name;
    unsigned int _reward;

    static bool huntActive;
};
