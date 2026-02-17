#pragma once

#include "ccompanion.h"

class CSupportCompanion : public CCompanion
{

public:
    CSupportCompanion(const std::string_view& moduleName, const std::string_view& objectName);

    static std::function<bool(const CSupportCompanion*)> companionModuleNameFilter(const std::string_view& moduleName);
    static std::function<bool(const CSupportCompanion*)> companionNameFilter(const std::string_view& name);

    static std::function<bool(CSupportCompanion*)> filterAndRemoveByModuleName(const std::string_view& moduleName);
    static std::function<bool(CSupportCompanion*)> filterAndRemoveByName(const std::string_view& moduleName);

    virtual std::string type() const override;

    virtual void preBattle(CEnemy* enemy) override;
    virtual void battleAction(CEnemy* enemy, bool& endRound) override;
    virtual void postBattle(CEnemy* enemy) override;
    virtual int shield(const int i) override;

    virtual void joinText() const;
    virtual void leaveText() const;

    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

protected:
    virtual std::string translatorModuleName() const override;

private:
    std::string _moduleName;
};
