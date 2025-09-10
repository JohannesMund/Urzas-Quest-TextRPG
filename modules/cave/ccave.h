#pragma once

#include "cfield.h"

class CCave : public CRoom
{
public:
    CCave();

    virtual void execute() override;

    virtual std::string bgColor() const override;
    virtual std::string fgColor() const override;

    void setOpen(const bool bOpen);

    static CMap::RoomFilter caveFilter();

    virtual bool isTaskPossible(const std::string_view& moduleName) const override;

protected:
    virtual nlohmann::json save() const override;
    virtual bool load(const nlohmann::json& json) override;

private:
    void initDungeon();
    virtual char getMapSymbol() const override;

    bool _isOpen = false;
};
