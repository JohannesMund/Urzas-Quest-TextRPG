#pragma once

#include "citem.h"
#include <nlohmann/json_fwd.hpp>

class CBasicDjinn;
class CWonderLamp : public CItem
{
public:
    CWonderLamp();
    ~CWonderLamp();
    virtual void useFromInventory() override;
    virtual void useFromBattle(CEnemy*) override;

    static CItem::ItemFilter wonderlampFilter();

    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

protected:
    virtual std::string translatorModuleName() const override;

private:
    void rubTheLamp();
    void examine();

    void useWish();
    void adjustWishes();
    void destroy();

    bool _wasted = false;
    int _wishesLeft = 3;

    CBasicDjinn* _djinn;
};