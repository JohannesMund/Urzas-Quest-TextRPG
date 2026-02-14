#include "ctranslatable.h"

std::string CTranslatable::coreTr(const std::string_view& textId) const
{
    return CTranslator::tr(TagNames::Translator::core, translatorObjectName(), textId);
}

std::string CTranslatable::tr(const std::string_view& textId) const
{
    return CTranslator::tr(translatorModuleName(), translatorObjectName(), textId);
}
