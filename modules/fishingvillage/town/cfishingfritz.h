#pragma once

#include "ctranslatable.h"

#include <string>

class CFishingFritz : public CTranslatable
{
public:
    CFishingFritz();

    void execute();

protected:
    virtual std::string translatorModuleName() const override;
    virtual std::string translatorObjectName() const override;

private:
    void printHeader() const;

    bool isOpen() const;

    void ask();
    void checkFish();

    void getInformation() const;

    void sell() const;

    void enhance() const;

    bool isMakeRodActive() const;
    bool isMakeBoatActive() const;
    bool hasFish() const;
    std::string sellYourFish() const;

    bool _firstVisit = true;
};
