#include "companionfactory.h"

#include "cattackercompanion.h"
#include "cdefendercompanion.h"
#include "chealercompanion.h"
#include "cscarymonstercompanion.h"
#include "ressources.h"

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
