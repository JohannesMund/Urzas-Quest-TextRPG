#include "ctranslator.h"
#include "console.h"
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

CTranslator::CTranslator()
{

    loadTranslationFile("core", "ressources/core/ressources.json");
}

void CTranslator::registerModule(const std::string_view& moduleName, const std::string_view& fileName)
{
    loadTranslationFile(moduleName, std::format("./ressources/modules/{}.json", fileName));
}

std::string CTranslator::translate(const std::string_view& moduleName,
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

        path.append("/").append(objectName);

        if (!t.contains(path))
        {
            throw Translator::CTranslatorException(std::format("Translator object {} not found", path));
        }

        path.append("/").append(textId);

        if (!t.contains(path))
        {
            throw Translator::CTranslatorException(std::format("Translator string {} not found", path));
        }

        return t[path].get<std::string>();
    }
    catch (const Translator::CTranslatorException& e)
    {
        Console::printErr("Translation error", e.what());
    }
    return std::string(textId);
}
