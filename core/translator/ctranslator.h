#pragma once

#include <map>
#include <string>

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

    std::string getTranslatorFile(const std::string& moduleName);
    std::map<std::string, std::string> _translationFiles;

    bool checkTranslationFile(const std::string& file);
};