#pragma once

#include "menuaction.h"

#include <string>

/**
 * @brief represents a menu actiom
 * @sa CMenu
 * @remarks private costructor, must be created by CMenu
 * @sa CMenu::makeMenuAction
 */
class CMenuAction
{
    friend class CMenu;

public:
    bool operator==(const CMenuAction& other) const
    {
        return _key == other._key;
    }
    bool operator!=(const CMenuAction& other) const
    {
        return _key != other._key;
    }

    /**
     * @brief creates a invalid action
     * @remarks to be used to have a CMenuAction instance before beeing able to initialize it
     */
    CMenuAction();

    /**
     * @brief returns the name
     */
    std::string_view getName() const;

    /**
     * @brief returns the key
     */
    unsigned char getKey() const;

    /**
     * @brief checks, if the action is valid
     */
    bool isValid() const;

private:
    CMenuAction(const std::string_view& name, const std::string& display, const unsigned char key);

    std::string _name;
    std::string _display;
    unsigned char _key = 0;
};