#pragma once

#include "colorconsole.h"
#include "ressources.h"
#include <string>

class CEnemy;
class CCompanion
{
public:
    virtual ~CCompanion()
    {
    }

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

protected:
    bool fireDefaultAction() const;

    std::string _description;
    unsigned int _level = 0;
};
