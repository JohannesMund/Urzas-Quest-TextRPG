#pragma once

#include <map>
#include <string>

#include <nlohmann/json.hpp>

class CTranslator
{
    friend class CGameManagement;

public:
    static CTranslator* getInstance()
    {
        static CTranslator t;
        return &t;
    };

    void registerModule(const std::string_view& moduleName, const std::string_view& fileName);

    static std::string translate(const std::string_view& moduleName,
                                 const std::string_view& objectName,
                                 const std::string_view& textId);

private:
    CTranslator();

    nlohmann::json _translations;

    void checkTranslationFileExist(const std::string& file);
    void loadTranslationFile(const std::string_view& moduleName, const std::string& file);
};