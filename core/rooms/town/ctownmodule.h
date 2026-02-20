#pragma once

#include "cgamestateobject.h"

#include <string>

class CTownModule : public CGameStateObject
{
public:
    virtual void execute() = 0;
    void setCityName(const std::string& s);

    nlohmann::json save() const override;
    virtual void load(const nlohmann::json&) override;

protected:
    virtual std::string translatorObjectName() const override;
    virtual std::string translatorModuleName() const override;

    CTownModule(const std::string_view& objectName);
    std::string _cityName;
};
