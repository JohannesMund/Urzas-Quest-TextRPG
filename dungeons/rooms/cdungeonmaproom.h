#pragma once

#include <cdungeonroom.h>

class CDungeonMapRoom : public CDungeonRoom
{
public:
    CDungeonMapRoom();

    virtual void execute() override;
    virtual std::string mapSymbol() const override;

    virtual bool isSpecialRoom() const override;

    virtual bool isMapRevealed() const;

private:
    bool _isMapRevealed = false;
};
