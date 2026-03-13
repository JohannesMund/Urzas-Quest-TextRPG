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

bool CTask::isMovable() const
{
    return _isMovable;
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
    json[TagNames::Task::movable] = _isMovable;
    return json;
}

void CTask::load(const nlohmann::json& json)
{
    _isFinished = json.value<bool>(TagNames::Task::finished, false);
    _isAutoExecute = json.value<bool>(TagNames::Task::autoExecute, false);
    _isMovable = json.value<bool>(TagNames::Task::movable, false);
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
