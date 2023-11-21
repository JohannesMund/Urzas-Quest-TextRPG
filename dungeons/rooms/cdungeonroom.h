#pragma once

#include "croom.h"

#include <string>
class CDungeonRoom : public CRoom
{
public:
    CDungeonRoom();

    virtual void setDescription(const std::string_view& description);
    virtual void setModuleName(const std::string_view& moduleName);

    virtual bool isSpecialRoom() const override;

private:
    virtual char getMapSymbol() const override;
};
