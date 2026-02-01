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

void CTask::load(const nlohmann::json& json)
{
    _isFinished = json.value<bool>(TagNames::Task::finished, false);
    _isAutoExecute = json.value<bool>(TagNames::Task::autoExecute, false);
}

std::string CTask::coreTr(const std::string_view& textId) const
{
    return CTranslator::translate(TagNames::Translator::core, TagNames::Task::task, textId);
}

CTask::CTask(const std::string_view& objectName) : CGameStateObject(objectName)
{
}
