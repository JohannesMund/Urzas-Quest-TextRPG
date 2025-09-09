#include "companionfactory.h"

#include "cattackercompanion.h"
#include "cdefendercompanion.h"
#include "chealercompanion.h"
#include "cscarymonstercompanion.h"
#include "modules/leilarescue/companions/cguardcompanion.h"
#include "modules/leilarescue/companions/cleilacompanion.h"

#include "ressources.h"

#include <nlohmann/json.hpp>

namespace
{

bool compareObjectName(const std::string& objectName, const nlohmann::json& json)
{
    const auto name = CGameStateObject::getObjectNameFromJson(json);
    if (name.empty())
    {
        return false;
    }

    return name.compare(objectName) == 0;
};

}; // namespace

CCompanion* CompanionFactory::loadCompanionFromSaveGame(const nlohmann::json& json)
{
    const auto isObjectName = [&json](const std::string& objectName) { return compareObjectName(objectName, json); };
    CCompanion* newCompanion = nullptr;

    if (isObjectName("CAttackerCompanion"))
    {
        newCompanion = new CAttackerCompanion();
    }
    else if (isObjectName("CDefenderCompanion"))
    {
        newCompanion = new CDefenderCompanion;
    }
    else if (isObjectName("CHealerCompanion"))
    {
        newCompanion = new CHealerCompanion;
    }
    else if (isObjectName("CScaryMonsterCompanion"))
    {
        newCompanion = new CScaryMonsterCompanion;
    }

    if (newCompanion != nullptr)
    {
        newCompanion->load(json);
    }

    return newCompanion;
}

CSupportCompanion* CompanionFactory::loadSupportCompanionFromSaveGame(const nlohmann::json& json)
{
    const auto isObjectName = [&json](const std::string& objectName) { return compareObjectName(objectName, json); };
    CSupportCompanion* newCompanion = nullptr;

    if (isObjectName("CLeilyCompanion"))
    {
        newCompanion = new CLeilaCompanion;
    }
    else if (isObjectName("CGuardCompanion"))
    {
        newCompanion = new CGuardCompanion("");
    }

    if (newCompanion != nullptr)
    {
        newCompanion->load(json);
    }

    return newCompanion;
}

CCompanion* CompanionFactory::makeRandomCompanion()
{
    switch (Ressources::Companion::getRandomCompanionType())
    {
    case Ressources::Companion::ECompanionType::eAttacker:
    default:
        return new CAttackerCompanion();
    case Ressources::Companion::ECompanionType::eDefender:
        return new CDefenderCompanion();
    case Ressources::Companion::ECompanionType::eHealer:
        return new CHealerCompanion();
    case Ressources::Companion::ECompanionType::eScaryMonster:
        return new CScaryMonsterCompanion();
    }
}
