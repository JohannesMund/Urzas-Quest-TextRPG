#include "ctranslator.h"

#include "console.h"
#include "defaultsettings.h"
#include "localdirectory.h"
#include "translator/translatorexceptions.h"
#include "json/jsontagnames.h"

#include <format>
#include <fstream>
#include <nlohmann/json.hpp>

void CTranslator::checkTranslation(const std::string_view& moduleName)
{
    auto t = CTranslator::getInstance()->_translations;
    if (!t.contains(std::string(moduleName)))
    {
        throw Translator::CTranslatorException(std::format("Translator module {} not loaded", moduleName));
    }
}

void CTranslator::loadTranslationFile(const std::string_view& moduleName, const std::string& file)
{
    try
    {
        _translations.emplace(moduleName, new CTranslationFile(file));
    }
    catch (const std::exception& e)
    {
        CLog::error() << "Error lading Translation file " << file << ": " << e.what() << std::endl << std::flush;
    }
}

std::optional<std::string> CTranslator::translate(const std::string_view& moduleName,
                                                  const std::string_view& objectName,
                                                  const std::string_view& textId)
{
    try
    {
        return getTranslationFile(moduleName)->getTranslation(objectName, textId);
    }
    catch (const Translator::CTranslatorException& e)
    {
        CLog::error() << "Translation error in " << moduleName << ": " << e.what() << std::endl << std::flush;
    }
    return {};
}

std::optional<Menu::MenuAction> CTranslator::translate(const std::string_view& moduleName,
                                                       const std::string_view& objectName,
                                                       const Menu::MenuAction& action)
{
    try
    {
        return getTranslationFile(moduleName)->getTranslation(objectName, action);
    }
    catch (const Translator::CTranslatorException& e)
    {
        CLog::error() << "Translation error in " << moduleName << ": " << e.what() << std::endl << std::flush;
    }
    return {};
}

CTranslator::CTranslator()
{
    registerModule(TagNames::Translator::core, Settings::translationCoreFileBaseName);
}

CTranslator::~CTranslator()
{
    for (auto p : _translations)
    {
        delete p.second;
    }
}

void CTranslator::registerModule(const std::string_view& moduleName, const std::string_view& fileName)
{
    loadTranslationFile(moduleName, std::format("{}.json", fileName));
}

CTranslationFile* CTranslator::getTranslationFile(const std::string_view& moduleName)
{
    std::string mod(moduleName);
    auto t = CTranslator::getInstance()->_translations;
    if (!t.contains(std::string(mod)))
    {
        throw Translator::CTranslatorException(std::format("No translation for module {} loaded", mod));
    }
    return t.at(std::string(moduleName));
}

std::string CTranslator::tr(const std::string_view& moduleName,
                            const std::string_view& objectName,
                            const std::string_view& textId)
{
    const auto r = translate(moduleName, objectName, textId);
    if (!r.has_value())
    {
        return std::string(textId);
    }
    return *r;
}

Menu::MenuAction CTranslator::tr(const std::string_view& moduleName,
                                 const std::string_view& objectName,
                                 const Menu::MenuAction& action)
{
    const auto r = translate(moduleName, objectName, action);
    if (!r.has_value())
    {
        return action;
    }
    return *r;
}
