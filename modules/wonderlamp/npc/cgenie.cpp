#include "cgenie.h"
#include "colorize.h"
#include "wonderlamp/moduleressources.h"

CGenie::CGenie() : CBasicDjinn(Core::EGender::eMale)
{
}

void CGenie::talk()
{
}

std::string CGenie::name() const
{
    return std::string(WonderLamp::genie());
}

std::string CGenie::describe() const
{
    return std::string();
}

CMenuAction CGenie::npcNav(CMenu& menu) const
{
    return menu.createAction({CC::unColorizeString(WonderLamp::genie())});
}

void CGenie::printHeader(const bool) const
{
}
