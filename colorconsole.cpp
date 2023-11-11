#include "colorconsole.h"

#include <format>
#include <regex>

std::string CC::fgBlack()
{
    return "\e[030m";
}

std::string CC::fgRed()
{
    return "\e[031m";
}

std::string CC::fgGreen()
{
    return "\e[032m";
}

std::string CC::fgYellow()
{
    return "\e[033m";
}

std::string CC::fgBlue()
{
    return "\e[034m";
}

std::string CC::fgMagenta()
{
    return "\e[035m";
}

std::string CC::fgCyan()
{
    return "\e[036m";
}

std::string CC::fgLightGray()
{
    return "\e[037m";
}

std::string CC::fgDarkGray()
{
    return "\e[090m";
}

std::string CC::fgLightRed()
{
    return "\e[091m";
}

std::string CC::fgLightGreen()
{
    return "\e[092m";
}

std::string CC::fgLightYellow()
{
    return "\e[093m";
}

std::string CC::fgLightBlue()
{
    return "\e[094m";
}

std::string CC::fgLightMagenta()
{
    return "\e[095m";
}

std::string CC::fgLightCyan()
{
    return "\e[096m";
}

std::string CC::bgBlack()
{
    return "\e[040m";
}

std::string CC::bgRed()
{
    return "\e[041m";
}

std::string CC::bgGreen()
{
    return "\e[042m";
}

std::string CC::bgYellow()
{
    return "\e[043m";
}

std::string CC::bgBlue()
{
    return "\e[044m";
}

std::string CC::bgMagenta()
{
    return "\e[045m";
}

std::string CC::bgCyan()
{
    return "\e[046m";
}

std::string CC::bgLightGray()
{
    return "\e[047m";
}

std::string CC::bgDarkGray()
{
    return "\e[100m";
}

std::string CC::bgLightRed()
{
    return "\e[101m";
}

std::string CC::bgLightGreen()
{
    return "\e[102m";
}

std::string CC::bgLightYellow()
{
    return "\e[103m";
}

std::string CC::bgLightBlue()
{
    return "\e[104m";
}

std::string CC::bgLightMagenta()
{
    return "\e[105m";
}

std::string CC::bgLightCyan()
{
    return "\e[106m";
}

std::string CC::ccReset()
{
    return "\e[000m";
}

std::string CC::ccInvert()
{
    return "\e[007m";
}

std::string CC::colorizeString(const std::string_view& s, const std::string_view& c1, const std::string_view& c2)
{
    return std::format("{}{}{}{}{}", c1, s.at(0), c2, s.substr(1), CC::ccReset());
}

size_t CC::colorizedSize(const std::string& s)
{
    const std::regex expression("\\\e\\[(\\d*)m");

    auto beginIt = std::sregex_iterator(s.begin(), s.end(), expression);
    auto endIt = std::sregex_iterator();
    auto count = std::distance(beginIt, endIt);

    return s.size() - (count * colorCodeSize());
}

size_t CC::colorCodeSize()
{
    return std::string("\e[000m").size();
}

std::string CC::colorizedSubString(const std::string_view& text, const unsigned int from, const unsigned int size)
{
    std::string substring;
    auto len = from + size;
    for (auto i = from; i < len && i < text.size(); i++)
    {
        if (text.at(i) == '\e')
        {
            len += CC::colorCodeSize();
        }
        substring.push_back(text.at(i));
    }
    return substring;
}
