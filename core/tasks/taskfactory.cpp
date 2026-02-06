#include "taskfactory.h"
#include "cbountyhunt.h"
#include "cgamemanagement.h"
#include "console.h"
#include "ctask.h"
#include "json/jsonexceptions.h"

CTask* TaskFactory::loadTaskFromSaveGame(const nlohmann::json& json)
{
    CTask* newTask = nullptr;
    if (CGameStateObject::compareObjectName(TagNames::Task::bountyHunt, json))
    {
        newTask = new CBountyHunt("", 0);
    }
    else
    {
        newTask = CGameManagement::getInstance()->getProgressionInstance()->callModuleTaskFactory(
            CGameStateObject::getObjectNameFromJson(json));
    }

    if (newTask != nullptr)
    {
        try
        {
            newTask->load(json);
            return newTask;
        }
        catch (const Json::CJsonException& e)
        {
            Console::printErr("Load task error", e.what());
            delete newTask;
            return nullptr;
        }
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
