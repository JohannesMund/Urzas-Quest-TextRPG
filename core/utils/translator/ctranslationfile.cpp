#include "ctranslationfile.h"
#include "cgamemanagement.h"
#include "cgamesettings.h"
#include "translator/translatorexceptions.h"
#include "json/jsontagnames.h"

#include <format>
#include <localdirectory.h>

const std::string CTranslationFile::getTranslation(const std::string_view& objectName, const std::string_view& textId)
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
    return jIt.value();
}

void CTranslationFile::addTranslation(const std::string_view& objectName, const std::string_view& textId)
{
    if (!_document.contains(objectName))
    {
        _document[objectName] = nlohmann::json::array();
    }
    _document[objectName].push_back({{TagNames::Translator::source, textId}});
    dump();
}

std::string CTranslationFile::currentLanguageTag()
{
    auto lang = CGameManagement::getGameSettingsInstance()->currentLanguage();
    if (lang.compare("en") == 0)
    {
        return std::string(TagNames::Translator::source);
    }

    return std::string(lang);
}
