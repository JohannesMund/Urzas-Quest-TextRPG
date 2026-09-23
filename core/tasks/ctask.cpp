#include "ctask.h"
#include "translator/ctranslator.h"

#include <nlohmann/json.hpp>

bool CTask::isFinished()
{
    return _isFinished;
}

bool CTask::isAutoExecute() const
{
    return _isAutoExecute;
}

Menu::MenuAction CTask::taskNav() const
{
    return {};
}

std::string CTask::moduleName() const
{
    return {};
}

CTask::ETaskMovement CTask::taskMovement() const
{
    return _taskMovement;
}

char CTask::mapSymbol() const
{
    return '!';
}

nlohmann::json CTask::save() const
{
    nlohmann::json json;
    json[TagNames::Task::finished] = _isFinished;
    json[TagNames::Task::autoExecute] = _isAutoExecute;
    json[TagNames::Task::movement] = _taskMovement;
    return json;
}

void CTask::load(const nlohmann::json& json)
{
    _isFinished = json.value<bool>(TagNames::Task::finished, false);
    _isAutoExecute = json.value<bool>(TagNames::Task::autoExecute, false);
    _taskMovement = json.value<ETaskMovement>(TagNames::Task::movement, ETaskMovement::eNone);
}

std::string CTask::translatorObjectName() const
{
    return std::string(TagNames::Task::task);
}

std::string CTask::translatorModuleName() const
{
    return moduleName();
}

CTask::CTask(const std::string_view& objectName) : CGameStateObject(objectName)
{
}
