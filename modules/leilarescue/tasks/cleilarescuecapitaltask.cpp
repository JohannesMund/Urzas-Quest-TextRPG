#include "cleilarescuecapitaltask.h"
#include "../moduleressources.h"
#include "cgamemanagement.h"

CLeilaRescueCapitalTask::CLeilaRescueCapitalTask() : CTask(TagNames::LeilaRescue::leilaRescueCapital)
{
    CGameManagement::getPlayerInstance()->removeSupportCompanionsByModuleName(LeilaRescue::moduleName());
}

void CLeilaRescueCapitalTask::execute()
{
}
