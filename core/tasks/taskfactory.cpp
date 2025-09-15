#include "taskfactory.h"
#include "cbountyhunt.h"
#include "cgamemanagement.h"
#include "ctask.h"

CTask* TaskFactory::loadTaskFromSaveGame(const nlohmann::json& json)
{
    CTask* newTask = nullptr;
    if (CGameStateObject::compareObjectName(TagNames::Task::bountyHunt, json))
    {
        newTask = new CBountyHunt("", 0);
    }

    if (newTask != nullptr)
    {
        if (newTask->load(json) == true)
        {
            return newTask;
        }
        delete newTask;
        return nullptr;
    }

    newTask = CGameManagement::getInstance()->getProgressionInstance()->callModuleTaskFactory(
        CGameStateObject::getObjectNameFromJson(json));
    if (newTask != nullptr)
    {
        if (newTask->load(json) == true)
        {
            return newTask;
        }
        delete newTask;
    }
    return nullptr;
}

void TaskFactory::saveTaskToSaveGame(const CTask* task, nlohmann::json& json)
{
    nlohmann::json o = task->save();
    if (o.empty())
    {
        return;
    }
    o[TagNames::Common::objectName] = task->getObjectName();
    json[TagNames::Task::task] = o;
}
