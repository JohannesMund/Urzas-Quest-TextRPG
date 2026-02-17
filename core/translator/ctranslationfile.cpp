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
        updateTranslation(t, lang, textId);
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
        updateTranslation(t, lang, action);
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

template <typename T>
nlohmann::json CTranslationFile::findInArray(const std::string_view& objectName, const T& translatable)
{
    const auto jIt = std::find_if(_document[objectName].begin(),
                                  _document[objectName].end(),
                                  [&translatable](const nlohmann::json& jObject)
                                  {
                                      return jObject.contains(TagNames::Translator::source) &&
                                             compareTranslatable(jObject[TagNames::Translator::source], translatable);
                                  });

    if (jIt == _document[objectName].end())
    {
        return {};
    }
    return *jIt;
}

template <typename T>
void CTranslationFile::addTranslation(const std::string_view& objectName, const T& translatable)
{
    if (!CGameManagement::getGameSettingsInstance()->updateTranslations())
    {
        return;
    }
    if (!_document.contains(objectName))
    {
        _document.emplace(objectName, nlohmann::json::array());
    }
    _document[objectName].push_back(makeTranslationObject(translatable));
    dump();
}

template <typename T>
void CTranslationFile::updateTranslation(nlohmann::json& o, const std::string_view& language, const T& translatable)
{
    if (!CGameManagement::getGameSettingsInstance()->updateTranslations())
    {
        return;
    }
    emplaceIncomplete(o);
    o[language] = makeTranslatable(translatable);
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

nlohmann::json CTranslationFile::makeTranslatable(const std::string_view& textId)
{
    return nlohmann::json(textId);
}

nlohmann::json CTranslationFile::makeTranslatable(const Menu::MenuAction& action)
{
    return action.toJson();
}

bool CTranslationFile::compareTranslatable(const nlohmann::json& object, const std::string_view& textId)
{

    return object.get<std::string>() == textId;
}

bool CTranslationFile::compareTranslatable(const nlohmann::json& object, const Menu::MenuAction& action)
{
    return Menu::MenuAction::fromJson(object).name == action.name;
}

void CTranslationFile::emplaceUntranslated(nlohmann::json& o)
{
    o.emplace(TagNames::Translator::status, TagNames::Translator::untranslated);
}

void CTranslationFile::emplaceIncomplete(nlohmann::json& o)
{
    o.emplace(TagNames::Translator::status, TagNames::Translator::incomplete);
}
