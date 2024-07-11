#include "cleilarescuecapitaltask.h"
#include "../moduleressources.h"
#include "cgamemanagement.h"

CLeilaRescueCapitalTask::CLeilaRescueCapitalTask() : CTask()
{
    CGameManagement::getPlayerInstance()->removeSupportCompanionsByModuleName(LeilaRescueRessources::moduleName());
}

void CLeilaRescueCapitalTask::execute()
{
}
