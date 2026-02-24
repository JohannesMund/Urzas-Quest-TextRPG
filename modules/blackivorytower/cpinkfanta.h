#pragma once

#include "blackivorytower/moduleressources.h"
#include "citem.h"

class CPinkFanta : public CItem
{
public:
    CPinkFanta();

    static CItem::ItemFilter pinkFantaFilter();

    virtual void useFromInventory() override;
    virtual void useFromBattle(CEnemy*) override;

protected:
    virtual std::string translatorModuleName() const override;

private:
    void use();
};
