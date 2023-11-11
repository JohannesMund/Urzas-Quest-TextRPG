#pragma once

#include <cdungeonmap.h>

class CDungeonRoom;
class CCaveDungeonMap : public CDungeonMap
{
public:
    CCaveDungeonMap(const unsigned int width, const unsigned int height);

    virtual CDungeonRoom* makeDefaultRoom() const override;
};
