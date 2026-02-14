#pragma once

#include "ctranslator.h"

#include <format>
#include <string>

/**
 * @brief CTranslatable a virtual base-class for everything that contains translatable texts
 */

class CTranslatable
{

protected:
    /**
     * @brief Translate in the scope of the core
     * @remark baseclasses like CItem contain texts that are translated in the core. Classes derieved in Modules use
     * tr()
     * @param[in] textId the text to be translated
     * @param[in] formatArgs formatting args (used by std::format)
     */
    template <typename... Args>
    std::string coreTr(const std::string_view& textId, Args&&... formatArgs) const;

    /**
     * @brief Translate in the scope of the core
     * @remark baseclasses like CItem contain texts that are translated in the core. Classes derieved in Modules use
     * tr()
     * @param[in] textId the text to be translated
     */
    std::string coreTr(const std::string_view& textId) const;

    /**
     * @brief tr in the scope of a modile
     * @remark translatorModuleName must be implemented and return a non-empty string
     * @param[in] textId the text to be translated
     * @param[in] formatArgs formatting args (used by std::format)
     */
    template <typename... Args>
    std::string tr(const std::string_view& textId, Args&&... formatArgs) const;

    /**
     * @brief Translate in the scope of a modile
     * @remark translatorModuleName must be implemented and return a non-empty string
     * @param[in] textId the text to be translated
     */
    std::string tr(const std::string_view& textId) const;

private:
    /**
     * @brief returns the objectName used in the translator file
     * @remark must be implemented and returm a non empty string
     */
    virtual std::string translatorObjectName() const = 0;

    /**
     * @brief returns the moduleName used in the translator file
     * @remark must be implemented and returm a non empty string if translations shall be done on module scope
     */
    virtual std::string translatorModuleName() const = 0;
};

template <typename... Args>
inline std::string CTranslatable::coreTr(const std::string_view& textId, Args&&... formatArgs) const
{
    return CTranslator::tr(TagNames::Translator::core, translatorObjectName(), textId, formatArgs...);
}

template <typename... Args>
inline std::string CTranslatable::tr(const std::string_view& textId, Args&&... formatArgs) const
{
    return CTranslator::tr(translatorModuleName(), translatorObjectName(), textId, formatArgs...);
}