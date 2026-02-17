#pragma once

#include "ctown.h"

class CCapital : public CTown
{
public:
    CCapital();

    virtual void execute() override;

    virtual std::string bgColor() const override;
    virtual std::string fgColor() const override;

    static CMap::RoomFilter capitalFilter();

protected:
    virtual std::string translatorModuleName() const override;

    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

private:
    virtual char getMapSymbol() const override;

    bool _open = false;
};
