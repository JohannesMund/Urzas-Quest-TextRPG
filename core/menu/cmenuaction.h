#pragma once

#include "menuaction.h"

#include <string>

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

    CMenuAction();

    std::string_view getName() const;
    unsigned char getKey() const;
    bool isValid() const;

private:
    CMenuAction(const std::string_view& name, const std::string& display, const unsigned char key);

    std::string _name;
    std::string _display;
    unsigned char _key = 0;
};