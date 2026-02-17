#pragma once

#include "ctranslatable.h"
#include <string>

class CTownModule : public CTranslatable
{
public:
    virtual void execute() = 0;
    void setCityName(const std::string& s);

protected:
    virtual std::string translatorObjectName() const override;
    virtual std::string translatorModuleName() const override;

    CTownModule();
    std::string _cityName;
};
