#pragma once

#include <cdungeonroom.h>

class CSewerBossRoom : public CDungeonRoom
{
public:
    CSewerBossRoom(bool* isBossDefeated);

    virtual void execute() override;

    virtual bool isSpecialRoom() const override;

private:
    virtual char getMapSymbol() const override;

    bool* _bossDefeated;
};
