#pragma once

#include <ctask.h>

class CTattooParlor : public CTask
{
public:
    CTattooParlor();

    virtual void execute() override;
    virtual bool isMovable() const override;

private:
    void tattooParlor();
    void askForRemoval();
    void coverUp();
    void printTattoos();
};
