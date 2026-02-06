#pragma once

#include <nlohmann/json_fwd.hpp>

class CCompanion;
class CSupportCompanion;

namespace CompanionFactory
{
CCompanion* loadCompanionFromSaveGame(const nlohmann::json& json);
CSupportCompanion* loadSupportCompanionFromSaveGame(const nlohmann::json& json);

CCompanion* makeRandomCompanion();
} // namespace CompanionFactory
