#include "ctask.h"

#include <nlohmann/json.hpp>

bool CTask::isFinished()
{
    return _isFinished;
}

bool CTask::isAutoExecute() const
{
    return _isAutoExecute;
}

std::string CTask::taskNav() const
{
    return {};
}

std::string CTask::moduleName() const
{
    return {};
}

nlohmann::json CTask::save() const
{
    nlohmann::json j;
    j[TagNames::Task::finished] = _isFinished;
    j[TagNames::Task::autoExecute] = _isAutoExecute;
    return j;
}

bool CTask::load(const nlohmann::json& json)
{
    _isFinished = json.value<bool>(TagNames::Task::finished, false);
    _isAutoExecute = json.value<bool>(TagNames::Task::autoExecute, false);
    return false;
}

CTask::CTask(const std::string_view& objectName) : CGameStateObject(objectName)
{
}
