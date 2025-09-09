#include "cgamestateobject.h"

#include <nlohmann/json.hpp>

const std::string CGameStateObject::_objectNameTag = "objectName";

CGameStateObject::CGameStateObject(const std::string_view& objectName) : _objectName(objectName)
{
}

std::string CGameStateObject::getObjectName() const
{
    return _objectName;
}

std::string CGameStateObject::getObjectNameFromJson(const nlohmann::json& json)
{
    return json.value<std::string>(_objectNameTag, "");
}

void CGameStateObject::addObjectNameToJson(nlohmann::json& json, const CGameStateObject* object)
{
    if (object == nullptr)
    {
        return;
    }

    json[_objectNameTag] = object->getObjectName();
}
