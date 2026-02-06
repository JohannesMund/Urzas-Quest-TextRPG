#pragma once

#include <fstream>
#include <iostream>
class CLog
{
public:
    ~CLog();

    static std::ofstream& info()
    {
        return makeEntry("Information");
    }

    static std::ofstream& error()
    {
        return makeEntry("Error");
    }

    static std::ofstream& warning()
    {
        return makeEntry("Warning");
    }

private:
    static std::ofstream& makeEntry(const std::string_view& scope);

    CLog();
    std::ofstream _os;
};