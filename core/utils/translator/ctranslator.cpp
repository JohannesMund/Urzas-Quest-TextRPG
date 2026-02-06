#include "ctranslator.h"
#include "clog.h"
#include "console.h"
#include "localdirectory.h"
#include "translator/translatorexceptions.h"
#include "json/jsontagnames.h"

#include <format>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

void CTranslator::loadTranslationFile(const std::string_view& moduleName, const std::string& file)
{
    try
    {
        CTranslationFile fl(file);
        _translations.emplace(moduleName, fl);
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
        auto t = CTranslator::getInstance()->_translations;
        if (!t.contains(moduleName))
        {
            throw Translator::CTranslatorException(std::format("Translator module {} not loaded", moduleName));
        }

        return t.at(moduleName).getTranslation(objectName, textId);
    }
    catch (const Translator::CTranslatorException& e)
    {
        CLog::error() << "Translation error in " << moduleName << ": " << e.what() << std::endl << std::flush;
    }
    return {};
}

CTranslator::CTranslator()
{
    registerModule("core", "core");
}

void CTranslator::registerModule(const std::string_view& moduleName, const std::string_view& fileName)
{
    loadTranslationFile(moduleName, std::format("{}.json", fileName));
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

template <typename... Args>
std::string CTranslator::tr(const std::string_view& moduleName,
                            const std::string_view& objectName,
                            const std::string_view& textId,
                            Args&&...)
{
    const auto r = translate(moduleName, objectName, textId);
    if (!r.has_value())
    {
        return std::string(textId);
    }

    try
    {
        return *r;
        // return std::format(std::runtime_format(*r), std::make_format_args(formatArgs...));
    }
    catch (const std::exception& e)
    {
        CLog::error() << "Formatting error, std::format threw: " << e.what() << std::endl << std::flush;
        return *r;
    }
}
