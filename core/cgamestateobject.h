#pragma once
#include <nlohmann/json.hpp>
#include <string>

class CGameStateObject
{
public:
    explicit CGameStateObject(const std::string& objectName);
    std::string getObjectName() const;

    virtual nlohmann::json save() const = 0;

private:
    const std::string _objectName;
};