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

private:
    const std::string _name;
    const unsigned int _reward;

    static bool huntActive;
};
