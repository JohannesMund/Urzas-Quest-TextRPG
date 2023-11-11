#pragma once

#include <string>

class CTownModule
{
public:
    virtual void execute() = 0;
    void setCityName(const std::string& s);

protected:
    CTownModule();
    std::string _cityName;
};
