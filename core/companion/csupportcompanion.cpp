#include "csupportcompanion.h"
#include "console.h"
#include "csavefile.h"
#include "ressources.h"

#include <format>
#include <nlohmann/json.hpp>

CSupportCompanion::CSupportCompanion(const std::string_view& moduleName, const std::string_view& objectName) :
    CCompanion(objectName),
    _moduleName(moduleName)
{
}

std::function<bool(const CSupportCompanion*)> CSupportCompanion::companionModuleNameFilter(
    const std::string_view& moduleName)
{
    return [&moduleName](const CSupportCompanion* companion)
    { return companion->_moduleName.compare(moduleName) == 0; };
}

std::function<bool(const CSupportCompanion*)> CSupportCompanion::companionNameFilter(const std::string_view& name)
{
    return [&name](const CSupportCompanion* companion) { return companion->_moduleName.compare(name) == 0; };
}

std::function<bool(CSupportCompanion*)> CSupportCompanion::filterAndRemoveByModuleName(
    const std::string_view& moduleName)
{
    return [&moduleName](CSupportCompanion* c)
    {
        if (companionModuleNameFilter(moduleName)(c))
        {
            delete c;
            return true;
        }
        return false;
    };
}

std::function<bool(CSupportCompanion*)> CSupportCompanion::filterAndRemoveByName(const std::string_view& name)
{
    return [&name](CSupportCompanion* c)
    {
        if (companionNameFilter(name)(c))
        {
            delete c;
            return true;
        }
        return false;
    };
}

std::string CSupportCompanion::type() const
{
    return "";
}

void CSupportCompanion::preBattle(CEnemy*)
{
}

void CSupportCompanion::battleAction(CEnemy*, bool&)
{
}

void CSupportCompanion::postBattle(CEnemy*)
{
}

int CSupportCompanion::shield(const int i)
{
    return i;
}

void CSupportCompanion::joinText() const
{
    Console::printLn(std::format("{} joins you", name()));
}

void CSupportCompanion::leaveText() const
{
    Console::printLn(std::format("{} leaves you", name()));
}

nlohmann::json CSupportCompanion::save() const
{
    nlohmann::json o = CCompanion::save();
    o[TagNames::Common::moduleName] = _moduleName;
    return o;
}

bool CSupportCompanion::load(const nlohmann::json& json)
{
    _moduleName = json.value<std::string>(TagNames::Common::moduleName, "");
    if (_moduleName.empty())
    {
        return false;
    }

    return CCompanion::load(json);
}
