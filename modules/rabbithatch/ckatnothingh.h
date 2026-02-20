#pragma once
#include "cnpc.h"

class CKatNothingH : public CNpc
{
public:
    CKatNothingH();

    virtual void interact() override;
    virtual void talk() override;
    virtual void thinkAbout() override;

    virtual std::string name() const override;
    virtual std::string describe() const override;

protected:
    virtual std::string translatorModuleName() const override;

private:
    void printHeader();
};
