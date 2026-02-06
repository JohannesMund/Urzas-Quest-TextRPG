#pragma once
#include <format>
#include <nlohmann/json.hpp>

namespace Json
{

/**
 * @brief An exception to be thrown by the saveGame
 * @remark Does not inherit json exception
 * @remark can be constructed around a json exception
 */

class CJsonException : public std::exception
{
public:
    CJsonException(const nlohmann::json::exception& e) : std::exception()
    {
        _what = std::format("Json Exception: ", e.what());
    }
    CJsonException(const std::string_view& what) : std::exception()
    {
        _what = std::format("Json Exception: {}", what);
    }
    virtual const char* what() const throw()
    {
        return _what.c_str();
    }

private:
    std::string _what;
};

} // namespace Json