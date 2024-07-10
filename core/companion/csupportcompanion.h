#pragma once

#include "ccompanion.h"

class CSupportCompanion : public CCompanion
{

public:
    CSupportCompanion(const std::string_view& moduleName);

    static std::function<bool(const CSupportCompanion*)> companionModuleNameFilter(const std::string_view& moduleName);
    static std::function<bool(const CSupportCompanion*)> companionNameFilter(const std::string_view& name);

    static std::function<bool(CSupportCompanion*)> filterAndRemoveByModuleName(const std::string_view& moduleName);
    static std::function<bool(CSupportCompanion*)> filterAndRemoveByName(const std::string_view& moduleName);

    virtual std::string type() const override;

    virtual void preBattle(CEnemy* enemy) override;
    virtual void battleAction(CEnemy* enemy, bool& endRound) override;
    virtual void postBattle(CEnemy* enemy) override;
    virtual int shield(const int i) override;

private:
    std::string _moduleName;
};
