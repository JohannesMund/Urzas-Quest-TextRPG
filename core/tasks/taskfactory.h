#pragma once

#include <nlohmann/json_fwd.hpp>

class CTask;
namespace TaskFactory
{
CTask* loadTaskFromSaveGame(const nlohmann::json& json);
}