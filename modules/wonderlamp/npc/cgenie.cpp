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

std::string CGenie::colorize(const std::string_view& s) const
{
    return WonderLamp::colorizeGenie(s);
}

void CGenie::printHeader(const bool) const
{
}
