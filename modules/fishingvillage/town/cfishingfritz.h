#pragma once

#include <string>

class CFishingFritz
{
public:
    CFishingFritz();

    void execute();

private:
    void printHeader() const;

    bool isOpen() const;

    void ask() const;
    void buildRod() const;
    void buildBoat() const;
    void getInformation() const;

    void sell() const;

    void enhance() const;

    bool isMakeRodActive() const;
    bool isMakeBoatActive() const;
    bool hasFish() const;
    std::string sellYourFish() const;
};
