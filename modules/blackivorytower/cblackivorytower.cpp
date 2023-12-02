#include "cblackivorytower.h"
#include "cgamemanagement.h"
#include "cgameprogression.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "moduleressources.h"

#include <format>

CBlackIvoryTower::CBlackIvoryTower() : CField()
{
    _encounterType = CEncounter::EEncounterType::eNone;
    _isRandomTaskPossible = false;
    _showInFogOfWar = true;
}

void CBlackIvoryTower::execute()
{

    CField::execute();

    if (!_isOpen &&
        !CGameManagement::getProgressionInstance()->isModuleQuestAccepted(BlackIvoryTowerRessources::moduleName()))
    {

        printHeader(0);
        Console::printLn("Big tower");
        Console::printLn("Closed");
        Console::confirmToContinue();
        return;
    }

    CMenu::Action input;
    CMenu menu;
    menu.addMenuGroup({menu.createAction("Climb")}, {CMenu::exit()});

    do
    {
        printHeader(0);
        Console::printLn("Big tower");

        input = menu.execute();
        if (input.key == 'c')
        {
            climb();
        }
    } while (input != CMenu::exit());
}

std::string CBlackIvoryTower::bgColor() const
{
    return CC::bgBlack();
}

std::string CBlackIvoryTower::fgColor() const
{
    return CC::fgLightYellow();
}

char CBlackIvoryTower::getMapSymbol() const
{
    return '#';
}

CMap::RoomFilter CBlackIvoryTower::towerFilter()
{
    return [](const CRoom* room) { return dynamic_cast<const CBlackIvoryTower*>(room) != nullptr; };
}

void CBlackIvoryTower::climb()
{
    unsigned int currentStage = 1;
    while (currentStage != 0)
    {

        executeStairs(currentStage);

        CMenu menu;
        CMenu::ActionList downAction = {menu.createAction("Down", 'd')};
        CMenu::ActionList upAction = {};
        if (currentStage >= 25)
        {
            upAction.push_back(menu.createAction("Visit Office", 'V'));
        }
        else
        {
            upAction.push_back(menu.createAction("Up", 'u'));
        }
        menu.addMenuGroup(downAction, upAction);
        auto input = menu.execute();
        if (input.key == 'd')
        {
            currentStage--;
        }
        if (input.key == 'u')
        {
            currentStage++;
        }
        if (input.key == 'v')
        {
            executeTopOffice();
        }
    }
}

void CBlackIvoryTower::executeTopOffice()
{
    printHeader(BlackIvoryTowerRessources::towerHeight);
    Console::printLn("Yay! oben!");
    _isOpen = true;

    Console::confirmToContinue();
}

void CBlackIvoryTower::executeStairs(const unsigned int stage)
{
    printHeader(stage);
}

void CBlackIvoryTower::printHeader(const unsigned int stage) const
{
    Console::cls();
    Console::printLn(BlackIvoryTowerRessources::darkIvoryTower(), Console::EAlignment::eCenter);

    if (stage == 0)
    {
        Console::printLn("Ground floor", Console::EAlignment::eCenter);
    }
    else if (stage >= BlackIvoryTowerRessources::towerHeight)
    {
        Console::printLn("Ground floor", Console::EAlignment::eCenter);
    }
    else
    {
        Console::printLn(std::format("Floor {}", stage));
    }
    Console::br();
}
