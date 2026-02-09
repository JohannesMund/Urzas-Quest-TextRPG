#pragma once

#include "menuaction.h"
#include "utils/json/cjsondocument.h"

/**
 * @brief CTranslationFile a file containing the translation for one module
 * @sa CTranslator
 * @sa CJsonDocument
 * @remark throws exceptions
 * @remark created and accessed by CTranslator
 */
class CTranslationFile : public CJsonDocument
{
    friend class CTranslator;

public:
    CTranslationFile(const std::string_view& fileName);

    std::string getTranslation(const std::string_view& objectName, const std::string_view& textId);
    Menu::MenuAction getTranslation(const std::string_view& objectName, const Menu::MenuAction& translationObject);

private:
    virtual void dump() const override;

    static std::string currentLanguageTag();

    void emplaceUntranslated(nlohmann::json& o);
    void emplaceIncomplete(nlohmann::json& o);

    void addTranslation(const std::string_view& objectName, const std::string_view& textId);
    void addTranslation(const std::string_view& objectName, const Menu::MenuAction& action);

    void updateTranslation(nlohmann::json& o, const std::string_view& language, const std::string_view& textId);
    void updateTranslation(nlohmann::json& o, const std::string_view& language, const Menu::MenuAction& action);

    nlohmann::json makeTranslationObject(const std::string_view& textId);
    nlohmann::json makeTranslationObject(const Menu::MenuAction& action);

    nlohmann::json findInArray(const std::string_view& objectName, const std::string_view& textId);
    nlohmann::json findInArray(const std::string_view& objectName, const Menu::MenuAction& action);

    std::string _fileBaseName;
};