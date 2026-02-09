#pragma once

#include <fstream>
#include <iostream>

/**
 * @brief CLog a tiny logger
 * @remark streams log infor to a fixed file in HomeDir
 * @remark rolls over everytime the app starts
 */

class CLog
{
    /**
     * only main should be able to rollover
     */
    friend int main();

public:
    ~CLog();

    /**
     * @brief info log an information
     * @example CLog::info() << "This is an information" << endl << flush;
     */
    static std::ofstream& info()
    {
        return makeEntry("Information");
    }

    /**
     * @brief error log an error
     * @example CLog::info() << "This is an error" << endl << flush;
     */
    static std::ofstream& error()
    {
        return makeEntry("Error");
    }

    /**
     * @brief info log an warning
     * @example CLog::warnign() << "This is an warning" << endl << flush;
     */
    static std::ofstream& warning()
    {
        return makeEntry("Warning");
    }

private:
    static std::ofstream& makeEntry(const std::string_view& scope);

    static void rollover();
    CLog();
    std::ofstream _os;
};