#include "ctranslatable.h"

std::string CTranslatable::coreTr(const std::string_view& textId) const
{
    return CTranslator::tr(TagNames::Translator::core, translatorObjectName(), textId);
}

std::string CTranslatable::tr(const std::string_view& textId) const
{
    return CTranslator::tr(getTranslatorModuleName(), translatorObjectName(), textId);
}

std::string CTranslatable::getTranslatorModuleName() const
{
    const auto moduleName = translatorModuleName();
    if (moduleName.empty())
    {
        assert(!"Modulename is empty, Translations on Modulescope need a moduleName");
    }
    return moduleName;
}
