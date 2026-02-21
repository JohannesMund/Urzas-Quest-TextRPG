#pragma once

#include <citem.h>

class CRabbithatchApple : public CItem
{
public:
    CRabbithatchApple();
    virtual void useFromInventory() override;
    virtual void useFromBattle(CEnemy*) override;

protected:
    virtual std::string translatorModuleName() const override;

private:
    void use();
};
