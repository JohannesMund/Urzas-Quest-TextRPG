#pragma once

#include <cdungeonroom.h>

class CLeilaPrisonRoom : public CDungeonRoom
{
public:
    CLeilaPrisonRoom(bool* isLeilaFreed);

    virtual void execute() override;

    virtual bool isSpecialRoom() const override;

private:
    virtual char getMapSymbol() const override;

    bool* _isLeilaFreed;
};
