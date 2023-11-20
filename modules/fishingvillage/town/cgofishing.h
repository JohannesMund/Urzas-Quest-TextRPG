#pragma once

class CFishingRod;
class CEquipment;
class CGoFishing
{
public:
    CGoFishing();

    void execute();

private:
    void init();
    void printItemLevels();
    void catchAFish();
    CEquipment* _fishingRod = nullptr;
    CEquipment* _boat = nullptr;
};
