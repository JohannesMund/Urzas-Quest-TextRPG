#include "ccollectpartsencounter.h"
#include "cbattle.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "cmobenemy.h"
#include "colorize.h"
#include "console.h"
#include "fishingvillage/items/cboatpart.h"
#include "fishingvillage/items/cfishingrodpart.h"
#include "moduleressources.h"
#include "randomizer.h"

#include <format>

CCollectPartsEncounter::CCollectPartsEncounter(const std::string_view& moduleName)
{
    _isSingleExecution = false;
    _type = CEncounter::eField;
    _moduleName = moduleName;
}

void CCollectPartsEncounter::execute(const std::string_view& moduleName)
{
    CEncounter::execute();

    if (_moduleName.compare(FishingVillageRessources::moduleNameMakeRod()) == 0)
    {
        findFishingRodPart();
    }
    else
    {
        findBoatPart();
    }
}

unsigned int CCollectPartsEncounter::encounterChance(const EEncounterType& tp, const std::string_view& moduleName) const
{
    return 15;
}

std::string CCollectPartsEncounter::name() const
{
    if (_moduleName.compare(FishingVillageRessources::moduleNameMakeRod()) == 0)
    {
        return "Build your Fishing Rod";
    }
    else
    {
        return "Build your Boat";
    }
}

std::string CCollectPartsEncounter::moduleName() const
{
    return _moduleName;
}

void CCollectPartsEncounter::findFishingRodPart()
{
    auto item = new CFishingRodPart();

    Console::printLn(std::format("Walking through the land, you see {} lying next to your path. This would be great "
                                 "for building your {}Fishing Rod{} Do you want to pick it up?",
                                 item->name(),
                                 CC::fgLightCyan(),
                                 CC::ccReset()));

    if (CMenu::executeYesNoMenu() == CMenu::no())
    {
        Console::printLn("Not today... You don't like fish so much anyway.");
        return;
    }

    if (Randomizer::getRandom(3) == 0)
    {
        CMobEnemy enemy;

        switch (item->part())
        {
        case CFishingRodPart::EPart::eRod:
        default:
            enemy.setName(std::format("{}Crazy Dog{}", CC::fgLightGray(), CC::ccReset()));
            enemy.setWeapon("Strong Bite");
            break;
        case CFishingRodPart::EPart::eThread:
            enemy.setName(std::format("{0}Cr{1}az{0}y C{1}at{2}", CC::fgLightGray(), CC::fgDarkGray(), CC::ccReset()));
            enemy.setWeapon("Sharp Claws");
            break;
        case CFishingRodPart::EPart::eHook:
            enemy.setName(std::format("{}Crazy Bird{}", CC::fgDarkGray(), CC::ccReset()));
            enemy.setWeapon("Pointy Beak");
            break;
        }

        CBattle battle(&enemy);
        battle.fight();

        if (CGameManagement::getPlayerInstance()->isDead())
        {
            return;
        }
        if (!enemy.isDead())
        {
            return;
        }
    }
    CGameManagement::getInventoryInstance()->addItem(item);
}

void CCollectPartsEncounter::findBoatPart()
{
    auto item = new CBoatPart();

    Console::printLn(std::format("Walking through the land, you see {0} lying next to your path. You want a "
                                 "{1}Boat{2}? you need {0}. Pick it up?",
                                 item->name(),
                                 CC::fgYellow(),
                                 CC::ccReset()));

    if (CMenu::executeYesNoMenu() == CMenu::no())
    {
        Console::printLn("Not today... You don't like water anyway.");
        return;
    }

    if (Randomizer::getRandom(3) == 0)
    {
        CMobEnemy enemy;

        switch (item->part())
        {
        case CBoatPart::EPart::eBoard:
        default:
            enemy.setName(std::format("{}Crazy Woodcutter{}", CC::fgYellow(), CC::ccReset()));
            enemy.setWeapon("Axe");
            break;
        case CBoatPart::EPart::eNail:
            enemy.setName(std::format("{}Crazy {}Carpenter{}", CC::fgLightYellow(), CC::fgYellow(), CC::ccReset()));
            enemy.setWeapon("Hammer");
            break;
        case CBoatPart::EPart::eRope:
            enemy.setName(std::format("{}Mr. Roper{}", CC::fgLightYellow(), CC::ccReset()));
            enemy.setWeapon("Screwdriver");
            break;
        }

        CBattle battle(&enemy);
        battle.fight();

        if (CGameManagement::getPlayerInstance()->isDead())
        {
            return;
        }
        if (!enemy.isDead())
        {
            return;
        }
    }
    CGameManagement::getInventoryInstance()->addItem(item);
}
