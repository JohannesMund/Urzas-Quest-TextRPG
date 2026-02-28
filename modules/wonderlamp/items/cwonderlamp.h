#pragma once

#include "citem.h"
#include <nlohmann/json_fwd.hpp>

class CBasicDjinn;
class CDjinnCompanion;
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
    void visitBottle();

    void replaceGem();
    void stealGem();
    void clean();

    void useWish();
    void adjustWishes(const bool print = false);
    void destroy();
    bool needsCleaning();

    bool _wasted = false;
    int _wishesLeft = 3;
    int _lastCaredFor = 0;
    bool _missingGem = false;

    CBasicDjinn* _djinn;
    CDjinnCompanion* _djinnCompanion;
};