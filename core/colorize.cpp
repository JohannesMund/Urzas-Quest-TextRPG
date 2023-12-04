#include "colorize.h"

#include <format>
#include <regex>

std::string CC::fgBlack()
{
    return "\33[030m";
}

std::string CC::fgRed()
{
    return "\33[031m";
}

std::string CC::fgGreen()
{
    return "\33[032m";
}

std::string CC::fgYellow()
{
    return "\33[033m";
}

std::string CC::fgBlue()
{
    return "\33[034m";
}

std::string CC::fgMagenta()
{
    return "\33[035m";
}

std::string CC::fgCyan()
{
    return "\33[036m";
}

std::string CC::fgLightGray()
{
    return "\33[037m";
}

std::string CC::fgDarkGray()
{
    return "\33[090m";
}

std::string CC::fgLightRed()
{
    return "\33[091m";
}

std::string CC::fgLightGreen()
{
    return "\33[092m";
}

std::string CC::fgLightYellow()
{
    return "\33[093m";
}

std::string CC::fgLightBlue()
{
    return "\33[094m";
}

std::string CC::fgLightMagenta()
{
    return "\33[095m";
}

std::string CC::fgLightCyan()
{
    return "\33[096m";
}

std::string CC::fgWhite()
{
    return "\33[097m";
}

std::string CC::bgBlack()
{
    return "\33[040m";
}

std::string CC::bgRed()
{
    return "\33[041m";
}

std::string CC::bgGreen()
{
    return "\33[042m";
}

std::string CC::bgYellow()
{
    return "\33[043m";
}

std::string CC::bgBlue()
{
    return "\33[044m";
}

std::string CC::bgMagenta()
{
    return "\33[045m";
}

std::string CC::bgCyan()
{
    return "\33[046m";
}

std::string CC::bgLightGray()
{
    return "\33[047m";
}

std::string CC::bgDarkGray()
{
    return "\33[100m";
}

std::string CC::bgLightRed()
{
    return "\33[101m";
}

std::string CC::bgLightGreen()
{
    return "\33[102m";
}

std::string CC::bgLightYellow()
{
    return "\33[103m";
}

std::string CC::bgLightBlue()
{
    return "\33[104m";
}

std::string CC::bgLightMagenta()
{
    return "\33[105m";
}

std::string CC::bgLightCyan()
{
    return "\33[106m";
}

std::string CC::bgWhite()
{
    return "\33[107m";
}

std::string CC::ccReset()
{
    return "\33[000m";
}

std::string CC::ccInvert()
{
    return "\33[007m";
}

std::string CC::colorizeString(const std::string_view& s, const std::string_view& c1, const std::string_view& c2)
{
    return std::format("{}{}{}{}{}", c1, s.at(0), c2, s.substr(1), CC::ccReset());
}

size_t CC::colorizedSize(const std::string& s)
{
    const std::regex expression(colorCodeRegExp());

    auto beginIt = std::sregex_iterator(s.begin(), s.end(), expression);
    auto endIt = std::sregex_iterator();
    auto count = std::distance(beginIt, endIt);

    return s.size() - (count * colorCodeSize());
}

size_t CC::colorCodeSize()
{
    return std::string("\33[000m").size();
}

std::string CC::colorizedSubString(const std::string_view& text, const unsigned int from, const unsigned int size)
{
    std::string substring;
    auto len = from + size;
    for (auto i = from; i < len && i < text.size(); i++)
    {
        if (text.at(i) == '\33')
        {
            len += CC::colorCodeSize();
        }
        substring.push_back(text.at(i));
    }
    return substring;
}

std::string CC::unColorizeString(const std::string& s)
{
    const std::regex expression(colorCodeRegExp());
    return std::regex_replace(s, expression, "");
}

std::string CC::colorCodeRegExp()
{
    return "\\\33\\[(\\d*)m";
}

bool CC::isColorized(const std::string& s)
{
    const std::regex expression(colorCodeRegExp());
    return std::regex_search(s, expression);
}
