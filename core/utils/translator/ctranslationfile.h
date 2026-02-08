#pragma once

#include "utils/json/cjsondocument.h"

class CTranslationFile : public CJsonDocument
{
public:
    const std::string getTranslation(const std::string_view& objectName, const std::string_view& textId);
    CTranslationFile(const std::string_view& fileName);

private:
    virtual void dump() const override;
    nlohmann::json findInArray(const std::string_view& objectName, const std::string_view& textId);
    void addTranslation(const std::string_view& objectName, const std::string_view& textId);

    static std::string currentLanguageTag();
    nlohmann::json makeTranslationObject(const std::string_view& textId);
    nlohmann::json makeMenuActionTranslationObject(const std::string_view& textId, const unsigned char key);
    std::string _fileBaseName;
};