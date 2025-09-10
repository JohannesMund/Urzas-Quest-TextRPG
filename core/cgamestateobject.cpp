#include "cgamestateobject.h"

#include <nlohmann/json.hpp>

CGameStateObject::CGameStateObject(const std::string_view& objectName) : _objectName(objectName)
{
}

std::string CGameStateObject::getObjectName() const
{
    return _objectName;
}

std::string CGameStateObject::getObjectNameFromJson(const nlohmann::json& json)
{
    return json.value<std::string>(TagNames::Common::objectName, "");
}

void CGameStateObject::addObjectNameToJson(nlohmann::json& json, const CGameStateObject* object)
{
    if (object == nullptr)
    {
        return;
    }

    json[TagNames::Common::objectName] = object->getObjectName();
}
