#include "clog.h"

#include "localdirectory.h"
#include "ressources.h"

#include <chrono>
#include <format>
#include <iostream>

CLog::~CLog()
{
    _os << std::flush;
    _os.close();
}

std::ofstream& CLog::makeEntry(const std::string_view& scope)
{
    static CLog l;
    auto now = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
    l._os << std::format("{:%Y-%m-%d %H:%M:%S}", now);
    l._os << " - [";
    l._os << scope;
    l._os << "]: ";
    return l._os;
}

CLog::CLog()
{
    auto path = LocalDirectory::getLocalDirectoryPath();
    path.append(Ressources::Settings::logFileName);
    _os.open(path, std::ofstream::out | std::ofstream::app);
}
