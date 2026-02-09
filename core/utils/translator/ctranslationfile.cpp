#include "ctranslationfile.h"
#include "cgamemanagement.h"
#include "cgamesettings.h"
#include "translator/translatorexceptions.h"
#include "json/jsontagnames.h"

#include <format>
#include <iostream>
#include <localdirectory.h>

std::string CTranslationFile::getTranslation(const std::string_view& objectName, const std::string_view& textId)
{
    if (!_document.contains(objectName))
    {
        addTranslation(objectName, textId);
        throw Translator::CTranslatorException(std::format("Object {} does not exist", objectName));
    }

    auto t = findInArray(objectName, textId);
    if (t.empty())
    {
        addTranslation(objectName, textId);
        throw Translator::CTranslatorException(std::format("Text {} does not exist", textId));
    }

    auto lang = currentLanguageTag();
    if (!t.contains(lang))
    {
        throw Translator::CTranslatorException(std::format("Language {} not supported", lang));
    }

    auto translation = t[lang];
    if (translation.empty())
    {
        throw Translator::CTranslatorException(std::format("translation for {} missing", textId));
    }

    return translation;
}

Menu::MenuAction CTranslationFile::getTranslation(const std::string_view& objectName, const Menu::MenuAction& action)
{
    if (!_document.contains(objectName))
    {
        addTranslation(objectName, action);
        throw Translator::CTranslatorException(std::format("Object {} does not exist", objectName));
    }

    auto t = findInArray(objectName, action);
    if (t.empty())
    {
        addTranslation(objectName, action);
        throw Translator::CTranslatorException(std::format("Text {} does not exist", action.name));
    }

    auto lang = currentLanguageTag();
    if (!t.contains(lang))
    {
        throw Translator::CTranslatorException(std::format("Language {} not supported", lang));
    }

    auto translation = t[lang];
    if (translation.empty())
    {
        throw Translator::CTranslatorException(std::format("translation for {} missing", action.name));
    }

    return Menu::MenuAction::fromJson(translation);
}

CTranslationFile::CTranslationFile(const std::string_view& fileName) :
    CJsonDocument(fileName, "./ressources/", TagNames::FileSpec::typeTranslation),
    _fileBaseName(fileName)
{
    load();
}

void CTranslationFile::dump() const
{
    auto path = LocalDirectory::getLocalDirectoryPath();
    path.append(_fileBaseName);
    dumpAs(path.string());
}

nlohmann::json CTranslationFile::findInArray(const std::string_view& objectName, const std::string_view& textId)
{
    const auto jIt = std::find_if(_document[objectName].begin(),
                                  _document[objectName].end(),
                                  [&textId](const nlohmann::json& jObject)
                                  {
                                      return jObject.contains(TagNames::Translator::source) &&
                                             jObject[TagNames::Translator::source].get<std::string>() == textId;
                                  });

    if (jIt == _document[objectName].end())
    {
        return {};
    }
    return *jIt;
}

nlohmann::json CTranslationFile::findInArray(const std::string_view& objectName, const Menu::MenuAction& action)
{
    const auto jIt = std::find_if(
        _document[objectName].begin(),
        _document[objectName].end(),
        [&action](const nlohmann::json& jObject)
        {
            return jObject.contains(TagNames::Translator::source) &&
                   jObject[TagNames::Translator::source].contains(TagNames::Translator::menuAction) &&
                   jObject[TagNames::Translator::source][TagNames::Translator::menuAction].get<std::string>() ==
                       action.name;
        });

    if (jIt == _document[objectName].end())
    {
        return {};
    }
    return *jIt;
}

void CTranslationFile::addTranslation(const std::string_view& objectName, const std::string_view& textId)
{
    if (!_document.contains(objectName))
    {
        _document.emplace(objectName, nlohmann::json::array());
    }
    _document[objectName].push_back(makeTranslationObject(textId));

    dump();
}

void CTranslationFile::addTranslation(const std::string_view& objectName, const Menu::MenuAction& action)
{
    if (!_document.contains(objectName))
    {
        _document.emplace(objectName, nlohmann::json::array());
    }
    _document[objectName].push_back(makeTranslationObject(action));

    dump();
}

std::string CTranslationFile::currentLanguageTag()
{
    auto lang = CGameManagement::getGameSettingsInstance()->currentLanguage();
    if (CGameSettings::isSourceLanguage(lang))
    {
        return std::string(TagNames::Translator::source);
    }

    if (!CGameSettings::isSupportedLanguage(lang))
    {
        return std::string(TagNames::Translator::source);
    }
    return std::string(lang);
}

nlohmann::json CTranslationFile::makeTranslationObject(const std::string_view& textId)
{
    nlohmann::json o;
    emplaceUntranslated(o);
    o.emplace(TagNames::Translator::source, textId);
    for (auto lang : CGameSettings::supportedLanguages())
    {
        if (!CGameSettings::isSourceLanguage(lang))
        {
            o.emplace(lang, textId);
        }
    }
    return o;
}

nlohmann::json CTranslationFile::makeTranslationObject(const Menu::MenuAction& action)
{
    nlohmann::json o;

    nlohmann::json source = action.toJson();

    emplaceUntranslated(o);
    o.emplace(TagNames::Translator::source, source);
    for (auto lang : CGameSettings::supportedLanguages())
    {
        if (!CGameSettings::isSourceLanguage(lang))
        {
            o.emplace(lang, action.toJson());
        }
    }
    return o;
}

void CTranslationFile::emplaceUntranslated(nlohmann::json& o)
{
    o.emplace(TagNames::Translator::status, TagNames::Translator::untranslated);
}