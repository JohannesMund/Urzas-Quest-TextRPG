#pragma once

#include "clog.h"
#include "ctranslationfile.h"

#include <map>
#include <nlohmann/json.hpp>
#include <string>

/**
 * @brief The CTranslator class provides translation of strings throughout the whole program
 * @remark Translations are provided by json files. json files must be copied by cmake
 * @remark Modules provide their own translation file. Module translations must be registered @sa registerModule
 * @remark Note, that cmake expectes a ressource file and will not execute successfully if none exists.
 */

class CTranslator
{
    /**
     * only CGameProhression shall register translations
     */
    friend class CGameProgression;

public:
    /**
     * Singleton to avoid costly loading of json pbjects
     */
    static CTranslator* getInstance()
    {
        static CTranslator t;
        return &t;
    };

    /**
     * @brief provides a translation and applies format args
     * @remarks uses CTranslator::translate
     * @remarks this function should be used rather than formatting translated strings by hand, because formatting
     * errors are handled here.
     * @param[in] moduleName the moduleName which provides the translations or "core"
     * @param[in] objecName section in the translation. organisation is up to the module
     * @param[in] textId text to be translated
     * @param[in] formatArgs format args to be used by std::format
     * @return the translated text with formatting or the textId if an error occured @sa formatArgs
     */
    template <typename... Args>
    static std::string tr(const std::string_view& moduleName,
                          const std::string_view& objectName,
                          const std::string_view& textId,
                          Args&&... formatArgs);

    /**
     * @brief provides a translation
     * @remarks uses CTranslator::translate
     * @param[in] moduleName the moduleName which provides the translations or "core"
     * @param[in] objecName section in the translation. organisation is up to the module
     * @param[in] textId text to be translated
     * @return the translated text or the textId if an error occured
     */
    static std::string tr(const std::string_view& moduleName,
                          const std::string_view& objectName,
                          const std::string_view& textId);

    /**
     * @brief provides a translation for a MenuAction
     * @remarks uses CTranslator::translate
     * @remark used, to apply a custom hotkey to a MenuAction (i.e. [A]ction)
     * @param[in] moduleName the moduleName which provides the translations or "core"
     * @param[in] objecName section in the translation. organisation is up to the module
     * @param[in] action MenuAction to be translated
     * @return the translated action or the action if an error occured
     */
    static Menu::MenuAction tr(const std::string_view& moduleName,
                               const std::string_view& objectName,
                               const Menu::MenuAction& action);

private:
    CTranslator();
    ~CTranslator();

    std::map<std::string, CTranslationFile*> _translations;

    void checkTranslation(const std::string_view& moduleName);

    void loadTranslationFile(const std::string_view& moduleName, const std::string& file);
    void registerModule(const std::string_view& moduleName, const std::string_view& fileName);

    static CTranslationFile* getTranslationFile(const std::string_view& moduleName);

    static std::optional<std::string> translate(const std::string_view& moduleName,
                                                const std::string_view& objectName,
                                                const std::string_view& textId);

    static std::optional<Menu::MenuAction> translate(const std::string_view& moduleName,
                                                     const std::string_view& objectName,
                                                     const Menu::MenuAction& action);
};

template <typename... Args>
inline std::string CTranslator::tr(const std::string_view& moduleName,
                                   const std::string_view& objectName,
                                   const std::string_view& textId,
                                   Args&&... formatArgs)
{

    const auto r = translate(moduleName, objectName, textId);
    if (!r.has_value())
    {
        return std::string(textId);
    }

    try
    {

        return std::format(std::runtime_format(*r), std::make_format_args(formatArgs...));
    }
    catch (const std::exception& e)
    {
        CLog::error() << "Formatting error, std::format threw: " << e.what() << std::endl << std::flush;
        return *r;
    }
}
