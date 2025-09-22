#include "companionfactory.h"
#include "cattackercompanion.h"
#include "cdefendercompanion.h"
#include "cgamemanagement.h"
#include "chealercompanion.h"
#include "console.h"
#include "cscarymonstercompanion.h"
#include "csupportcompanion.h"
#include "ressources.h"
#include "save/exceptions.h"

#include <nlohmann/json.hpp>

CCompanion* CompanionFactory::loadCompanionFromSaveGame(const nlohmann::json& json)
{
    CCompanion* newCompanion = nullptr;

    if (CGameStateObject::compareObjectName(TagNames::Companion::attackCompanion, json))
    {
        newCompanion = new CAttackerCompanion();
    }
    else if (CGameStateObject::compareObjectName(TagNames::Companion::defenderCompanion, json))
    {
        newCompanion = new CDefenderCompanion;
    }
    else if (CGameStateObject::compareObjectName(TagNames::Companion::healerCompanion, json))
    {
        newCompanion = new CHealerCompanion;
    }
    else if (CGameStateObject::compareObjectName(TagNames::Companion::scaryMonsterCompanion, json))
    {
        newCompanion = new CScaryMonsterCompanion;
    }

    if (newCompanion != nullptr)
    {
        try
        {
            newCompanion->load(json);
            return newCompanion;
        }
        catch (const SaveFile::CSaveFileException& e)
        {
            Console::printErr(e.what());
            delete newCompanion;
            return nullptr;
        }
    }
    return nullptr;
}

CSupportCompanion* CompanionFactory::loadSupportCompanionFromSaveGame(const nlohmann::json& json)
{
    CSupportCompanion* newCompanion =
        CGameManagement::getInstance()->getProgressionInstance()->callModuleSupportCompanionFactory(
            CGameStateObject::getObjectNameFromJson(json));
    if (newCompanion != nullptr)
    {
        try
        {
            newCompanion->load(json);
            return newCompanion;
        }
        catch (const SaveFile::CSaveFileException& e)
        {
            Console::printErr(e.what());
            delete newCompanion;
        }
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
