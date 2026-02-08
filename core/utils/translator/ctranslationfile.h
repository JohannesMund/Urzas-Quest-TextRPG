#pragma once

#include "menuaction.h"
#include "utils/json/cjsondocument.h"

class CTranslationFile : public CJsonDocument
{
public:
    std::string getTranslation(const std::string_view& objectName, const std::string_view& textId);
    Menu::MenuAction getTranslation(const std::string_view& objectName, const Menu::MenuAction& translationObject);

    CTranslationFile(const std::string_view& fileName);

private:
    virtual void dump() const override;

    static std::string currentLanguageTag();

    void emplaceUntranslated(nlohmann::json& o);

    void addTranslation(const std::string_view& objectName, const std::string_view& textId);
    void addTranslation(const std::string_view& objectName, const Menu::MenuAction& action);

    nlohmann::json makeTranslationObject(const std::string_view& textId);
    nlohmann::json makeTranslationObject(const Menu::MenuAction& action);

    nlohmann::json findInArray(const std::string_view& objectName, const std::string_view& textId);
    nlohmann::json findInArray(const std::string_view& objectName, const Menu::MenuAction& action);

    std::string _fileBaseName;
};