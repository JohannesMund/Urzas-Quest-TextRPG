#include "cleilaprisonroom.h"
#include "cgamemanagement.h"
#include "modules/leilarescue/companions/cleilacompanion.h"

CLeilaPrisonRoom::CLeilaPrisonRoom(bool* isLeilaFreed)
{
    _description = "leilasPrison";
    _showInFogOfWar = true;
    _isLeilaFreed = isLeilaFreed;
    _seen = true;
    _isRandomTaskPossible = false;
    _encounterType = CEncounter::EEncounterType::eNone;
}

void CLeilaPrisonRoom::execute()
{
    if (*_isLeilaFreed == true)
    {
        return;
    }

    *_isLeilaFreed = true;
    CGameManagement::getPlayerInstance()->addSupportCompanion(new CLeilaCompanion());
}

bool CLeilaPrisonRoom::isSpecialRoom() const
{
    return true;
}

char CLeilaPrisonRoom::getMapSymbol() const
{
    return 'L';
}
