#pragma once

#include <cdungeonroom.h>

class CSewerBossRoom : public CDungeonRoom
{
public:
    CSewerBossRoom(bool* isBossDefeated);

    virtual void execute() override;
    virtual std::string mapSymbol() const override;

    virtual bool isSpecialRoom() const override;

private:
    bool* _bossDefeated;
};
