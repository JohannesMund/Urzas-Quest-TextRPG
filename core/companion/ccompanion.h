#pragma once

#include "cgamestateobject.h"
#include "colorize.h"
#include "ressources.h"

#include <functional>
#include <string>

class CEnemy;
class CCompanion : public CGameStateObject
{
public:
    CCompanion(const std::string& objectName);

    virtual ~CCompanion()
    {
    }

    static std::function<bool(const CCompanion*)> companionNameFilter(const std::string_view& name);

    virtual std::string name() const = 0;
    virtual std::string type() const = 0;
    std::string description() const;
    unsigned int level() const;
    bool hasCompanion() const;

    virtual void preBattle(CEnemy* enemy) = 0;
    virtual void battleAction(CEnemy* enemy, bool& endRound) = 0;
    virtual void postBattle(CEnemy* enemy) = 0;
    virtual int shield(const int i) = 0;

    void evolve();

    virtual nlohmann::json save() const override;

protected:
    bool fireDefaultAction() const;

    std::string _description;
    unsigned int _level = 0;
};
