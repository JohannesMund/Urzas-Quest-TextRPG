#pragma once
#include <format>
#include <nlohmann/json.hpp>

namespace SaveFile
{
class CSaveFileException : public std::exception
{
public:
    CSaveFileException(const nlohmann::json::exception& e) : std::exception()
    {
        _what = std::format("Json Exception: ", e.what());
    }
    CSaveFileException(const std::string_view& what) : std::exception()
    {
        _what = std::format("CSaveFile Exception: ", what);
    }
    virtual const char* what() const throw()
    {
        return _what.c_str();
    }

private:
    std::string _what;
};

} // namespace SaveFile