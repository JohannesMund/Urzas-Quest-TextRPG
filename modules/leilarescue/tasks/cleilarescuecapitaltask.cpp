#include "cleilarescuecapitaltask.h"
#include "../moduleressources.h"
#include "cgamemanagement.h"

CLeilaRescueCapitalTask::CLeilaRescueCapitalTask() : CTask(TagNames::LeilaRescue::leilaRescueCapital)
{
    CGameManagement::getPlayerInstance()->removeSupportCompanionsByModuleName(LeilaRescueRessources::moduleName());
}

void CLeilaRescueCapitalTask::execute()
{
}
