#pragma once

#include <cdungeonmap.h>

class CDungeonRoom;
class CSewerDungeonMap : public CDungeonMap
{
public:
    CSewerDungeonMap(const unsigned int width, const unsigned int height);

    virtual CDungeonRoom* makeDefaultRoom() const override;
};
