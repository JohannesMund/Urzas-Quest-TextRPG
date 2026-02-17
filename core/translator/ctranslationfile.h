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

    template <typename T>
    void addTranslation(const std::string_view& objectName, const T& translatable);

    template <typename T>
    void updateTranslation(nlohmann::json& o, const std::string_view& language, const T& translatable);

    template <typename T>
    nlohmann::json findInArray(const std::string_view& objectName, const T& translatable);

    nlohmann::json makeTranslationObject(const std::string_view& textId);
    nlohmann::json makeTranslationObject(const Menu::MenuAction& action);

    nlohmann::json makeTranslatable(const std::string_view& textId);
    nlohmann::json makeTranslatable(const Menu::MenuAction& action);

    static bool compareTranslatable(const nlohmann::json& object, const std::string_view& textId);
    static bool compareTranslatable(const nlohmann::json& object, const Menu::MenuAction& action);

    void emplaceUntranslated(nlohmann::json& o);
    void emplaceIncomplete(nlohmann::json& o);

    std::string _fileBaseName;
};