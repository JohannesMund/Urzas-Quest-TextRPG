#include "ctranslator.h"

#include <cassert>
#include <format>
#include <fstream>

bool CTranslator::checkTranslationFile(const std::string& file)
{
    std::ifstream f(file.c_str());
    return f.good();
}

CTranslator::CTranslator()
{
    _translationFiles.emplace("core", "ressources/core/ressources.json");
}

void CTranslator::registerModule(const std::string_view& moduleName, const std::string_view& fileName)
{
    const auto fn = std::format("./ressources/modules/{}.json", fileName);
    assert(false && checkTranslationFile(fn));
    _translationFiles.emplace(moduleName, fn);
}

std::string CTranslator::translate(const std::string_view&, const std::string_view&, const std::string_view&)
{
    return std::string();
}

std::string CTranslator::getTranslatorFile(const std::string& moduleName)
{

    if (!_translationFiles.contains(moduleName))

    {
        assert(false && "module not registered");
        return std::string();
    }

    return _translationFiles.at(moduleName);
}
