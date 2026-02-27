#include "cjeannie.h"
#include "colorize.h"
#include "wonderlamp/moduleressources.h"

CJeannie::CJeannie() : CBasicDjinn(Core::EGender::eFemale)
{
}

void CJeannie::talk()
{
}

std::string CJeannie::name() const
{
    return std::string(WonderLamp::genie());
}

std::string CJeannie::describe() const
{
    return std::string();
}

CMenuAction CJeannie::npcNav(CMenu& menu) const
{
    return menu.createAction({CC::unColorizeString(WonderLamp::genie())});
}

void CJeannie::printHeader(const bool) const
{
}
