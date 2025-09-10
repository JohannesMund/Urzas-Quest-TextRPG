#pragma once

#include "cfield.h"

class CBlackIvoryTower : public CRoom
{

public:
    CBlackIvoryTower();

    virtual void execute() override;

    virtual std::string bgColor() const override;
    virtual std::string fgColor() const override;

    virtual char getMapSymbol() const override;

protected:
    virtual nlohmann::json save() const override;
    virtual bool load(const nlohmann::json& json) override;

private:
    static CMap::RoomFilter towerFilter();
    void climb();

    void executeTopOffice();
    void executeStairs(const unsigned int stage);

    void printHeader(const unsigned int stage) const;
    void haveADoener();

    bool _isOpen = false;
    bool _hadADoener = false;
};