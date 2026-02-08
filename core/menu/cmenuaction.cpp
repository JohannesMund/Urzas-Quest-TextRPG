#include "cmenuaction.h"

CMenuAction::CMenuAction() : _name("Invalid"), _display("Invalid"), _key(0)
{
}

std::string_view CMenuAction::getName() const
{
    return _name;
}

unsigned char CMenuAction::getKey() const
{
    return _key;
}

bool CMenuAction::isValid() const
{
    return _key != 0 && _name != "Invalid" && _display != "Invalid";
}

CMenuAction::CMenuAction(const std::string_view& name, const std::string& display, const unsigned char key) :
    _name(name),
    _display(display),
    _key(key)
{
}