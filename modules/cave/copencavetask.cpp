#include "copencavetask.h"
#include "ccave.h"
#include "cgamemanagement.h"
#include "cmap.h"
#include "moduleressources.h"

COpenCaveTask ::COpenCaveTask()
{
    _isAutoExecute = true;
}

void COpenCaveTask::execute()
{
    auto room = dynamic_cast<CCave*>(CGameManagement::getInstance()->currentRoom());
    if (room != nullptr)
    {
        room->setOpen(true);
        _isFinished = true;
    }
}

std::string COpenCaveTask::moduleName() const
{
    return CaveRessources::moduleName();
}
