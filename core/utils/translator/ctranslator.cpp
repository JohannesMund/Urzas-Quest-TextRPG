#include "ctranslator.h"
#include "console.h"
#include "localdirectory.h"
#include "ressources/jsontagnames.h"
#include "save/exceptions.h"
#include "translator/exceptions.h"

#include <cassert>
#include <format>
#include <fstream>
#include <nlohmann/json.hpp>

void CTranslator::checkTranslationFileExist(const std::string& file)
{
    if (!std::filesystem::exists(file))
    {
        Translator::CTranslatorException(std::format("Translator file {} does not exist", file));
    }
}

void CTranslator::loadTranslationFile(const std::string_view& moduleName, const std::string& file)
{
    try
    {
        checkTranslationFileExist(file);

        std::ifstream f;
        f.open(file);
        if (!f.is_open())
        {
            throw Translator::CTranslatorException(std::format("Read file {} failed", file));
        }
        if (f.peek() == std::ifstream::traits_type::eof())
        {
            throw Translator::CTranslatorException(std::format("file {} is empty", file));
        }

        auto translation = nlohmann::json::parse(f);
        f.close();

        _translations[moduleName] = translation;
    }
    catch (Translator::CTranslatorException& e)
    {
        Console::printErr(std::format("Error lading Translation file {}", file), e.what());
    }
}

std::optional<std::string> CTranslator::translate(const std::string_view& moduleName,
                                                  const std::string_view& objectName,
                                                  const std::string_view& textId)
{
    try
    {
        auto t = CTranslator::getInstance()->_translations;
        std::string path{moduleName};

        if (!t.contains(path))
        {
            throw Translator::CTranslatorException(std::format("Translator module {} not loaded", path));
        }

        path.append("/").append(TagNames::Translator::translation);
        path.append("/").append(objectName);

        if (!t.contains(path))
        {
            throw Translator::CTranslatorException(std::format("Translator object {} not found", path));
        }

        path.append("/").append(textId);

        if (!t.contains(path))
        {
            CTranslator::getInstance()->updateTranslationFile(moduleName, objectName, textId);
            throw Translator::CTranslatorException(std::format("Translator string {} not found", path));
        }

        return t[path].get<std::string>();
    }
    catch (const Translator::CTranslatorException& e)
    {
        Console::printErr("Translation error", e.what());
    }
    return {};
}

void CTranslator::updateTranslationFile(const std::string_view& moduleName,
                                        const std::string_view& objectName,
                                        const std::string_view& textId)
{
    if (!_translations.contains(moduleName))
    {
        // We do not want to create new ressource files.
        return;
    }

    auto j = _translations[moduleName];

    if (!j[TagNames::Translator::translation].contains(objectName))
    {
        j[TagNames::Translator::translation][objectName] = nlohmann::json();
    }

    j[TagNames::Translator::translation][objectName][textId] = nlohmann::json();

    try
    {
        auto path = LocalDirectory::getLocalDirectoryPath();
        path.append(std::format("{}_updated.json", moduleName));
        std::ofstream f;
        f.open(path, std::ofstream::out | std::ofstream::trunc);
        if (!f.is_open())
        {
            throw Translator::CTranslatorException(std::format("Write file {} failed", path.string()));
        }
        f << j.dump(2).c_str() << std::flush;
        f.close();
    }
    catch (const Translator::CTranslatorException& e)
    {
        Console::printErr("Save file error", e.what());
    }
    catch (const nlohmann::json::exception& e)
    {
        Console::printErr("Dump json error", e.what());
    }
}

CTranslator::CTranslator()
{
    loadTranslationFile("core", "ressources/core/ressources.json");
}

void CTranslator::registerModule(const std::string_view& moduleName, const std::string_view& fileName)
{
    loadTranslationFile(moduleName, std::format("./ressources/modules/{}.json", fileName));
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
                            Args&&... formatArgs)
{
    const auto r = translate(moduleName, objectName, textId);
    if (!r.has_value())
    {
        return std::string(textId);
    }

    try
    {
        return *r;
        return std::format(std::runtime_format(*r), std::make_format_args(formatArgs...));
    }
    catch (const std::exception& e)
    {
        Console::printErr("Formattimg error error", std::format("{} threw {}", *r, e.what()));
        return *r;
    }
}
