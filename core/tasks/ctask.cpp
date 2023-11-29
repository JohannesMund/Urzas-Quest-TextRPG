#include "ctask.h"

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

CTask::CTask()
{
}
