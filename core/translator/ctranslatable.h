#pragma once

#include "ctranslator.h"

#include <format>
#include <nlohmann/json_fwd.hpp>
#include <string>

class CTranslatable
{

protected:
    template <typename... Args>
    std::string coreTr(const std::string_view& textId, Args&&... formatArgs) const;
    std::string coreTr(const std::string_view& textId) const;

    template <typename... Args>
    std::string tr(const std::string_view& textId, Args&&... formatArgs) const;
    std::string tr(const std::string_view& textId) const;

private:
    virtual std::string translatorObjectName() const = 0;
    virtual std::string translatorModuleName() const = 0;
};

template <typename... Args>
inline std::string CTranslatable::coreTr(const std::string_view& textId, Args&&... formatArgs) const
{
    return std::vformat(CTranslator::tr(TagNames::Translator::core, translatorObjectName(), textId),
                        std::make_format_args(formatArgs...));
}

template <typename... Args>
inline std::string CTranslatable::tr(const std::string_view& textId, Args&&... formatArgs) const
{
    return CTranslator::tr(translatorModuleName(), translatorObjectName(), textId, formatArgs...);
}