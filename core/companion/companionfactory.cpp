#include "companionfactory.h"

#include "cattackercompanion.h"
#include "cdefendercompanion.h"
#include "cgamemanagement.h"
#include "chealercompanion.h"
#include "cscarymonstercompanion.h"
#include "modules/leilarescue/companions/cguardcompanion.h"
#include "modules/leilarescue/companions/cleilacompanion.h"
#include "modules/leilarescue/moduleressources.h"

#include "ressources.h"

#include <nlohmann/json.hpp>

namespace
{

bool compareObjectName(const std::string_view& objectName, const nlohmann::json& json)
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
    const auto isObjectName = [&json](const std::string_view& objectName)
    { return compareObjectName(objectName, json); };
    CCompanion* newCompanion = nullptr;

    if (isObjectName(TagNames::Companion::attackCompanion))
    {
        newCompanion = new CAttackerCompanion();
    }
    else if (isObjectName(TagNames::Companion::defenderCompanion))
    {
        newCompanion = new CDefenderCompanion;
    }
    else if (isObjectName(TagNames::Companion::healerCompanion))
    {
        newCompanion = new CHealerCompanion;
    }
    else if (isObjectName(TagNames::Companion::scaryMonsterCompanion))
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
    CSupportCompanion* newCompanion =
        CGameManagement::getInstance()->getProgressionInstance()->callModuleSupportCompanionFaction(
            CGameStateObject::getObjectNameFromJson(json));
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
