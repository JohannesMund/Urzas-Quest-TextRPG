#pragma once

#include <citem.h>

class CApple : public CItem
{
public:
    CApple();
    virtual void useFromInventory() override;
    virtual void useFromBattle(CEnemy*) override;

    static CItem::ItemFilter aopleFilter();

protected:
    virtual std::string translatorModuleName() const override;

private:
    void use();
};
