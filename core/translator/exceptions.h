#pragma once
#include <format>
#include <nlohmann/json.hpp>

namespace Translator
{

/**
 * @brief An exception to be thrown by the translator
 * @remark Does not inherit json exception
 * @remark can be constructed around a json exception
 */

class CTranslatorException : public std::exception
{
public:
    CTranslatorException(const nlohmann::json::exception& e) : std::exception()
    {
        _what = std::format("Json Exception: ", e.what());
    }
    CTranslatorException(const std::string_view& what) : std::exception()
    {
        _what = std::format("CTranslator Exception: {}", what);
    }
    virtual const char* what() const throw()
    {
        return _what.c_str();
    }

private:
    std::string _what;
};

} // namespace Translator