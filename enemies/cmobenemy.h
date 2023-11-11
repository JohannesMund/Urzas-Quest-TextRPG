#pragma once

#include <cenemy.h>

class CMobEnemy : public CEnemy
{
public:
    CMobEnemy();

    virtual void battleAction(bool& endRound) override;

    void setName(const std::string& name);
    void setWeapon(const std::string& weapon);

private:
    void specialAttack();
    unsigned int _specialAttackChance = 0;
};
