#pragma once

#include <citem.h>

class CRabbithatchApple : public CItem
{
public:
    CRabbithatchApple();
    virtual void useFromInventory() override;
    virtual void useFromBattle(CEnemy*) override;

    static CItem::ItemFilter aopleFilter();

protected:
    virtual std::string translatorModuleName() const override;

private:
    void use();
};
