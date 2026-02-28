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

std::string CJeannie::colorize(const std::string_view& s) const
{
    return WonderLamp::colorizeJeannie(s);
}

void CJeannie::printHeader(const bool) const
{
}
