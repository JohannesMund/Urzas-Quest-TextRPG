#pragma once

#include "jsontagnames.h"

#include <nlohmann/json.hpp>
#include <string>

namespace Menu
{
/**
 * @brief a translatable MenuAction
 */
struct MenuAction
{
    std::string name;
    const unsigned char key = 0;

    static MenuAction fromJson(const nlohmann::json& o)
    {
        return {o[TagNames::Translator::menuAction], o[TagNames::Translator::menuActionKey]};
    }

    nlohmann::json toJson() const
    {
        nlohmann::json o;
        o[TagNames::Translator::menuAction] = name;
        o[TagNames::Translator::menuActionKey] = key;
        return o;
    }
};
} // namespace Menu