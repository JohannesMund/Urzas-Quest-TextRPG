#include "cgamestateobject.h"

CGameStateObject::CGameStateObject(const std::string& objectName) : _objectName(objectName)
{
}

std::string CGameStateObject::getObjectName() const
{
    return _objectName;
}
