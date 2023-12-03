#include "cblackivorytower.h"
#include "cbattle.h"
#include "cdarkmobi.h"
#include "cgamemanagement.h"
#include "cgameprogression.h"
#include "clunatic.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "moduleressources.h"
#include "randomizer.h"

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

    printHeader(0);
    Console::printLn(std::format("The tower is at least 250 feet hight and {}pich black{}, the walls are plated with "
                                 "something looking like ivory, but since it is black it is probably no ivory. Lets "
                                 "call it black ivory. The top of the tower is high up in the sky.",
                                 CC::fgDarkGray(),
                                 CC::ccReset()));
    Console::br();
    if (!_isOpen &&
        !CGameManagement::getProgressionInstance()->isModuleQuestAccepted(BlackIvoryTowerRessources::moduleName()))
    {
        Console::printLn("The only entry is locked, there is no way to get into the tower.");
        Console::confirmToContinue();
        return;
    }

    CMenu::Action input;
    CMenu menu;
    menu.addMenuGroup({menu.createAction("Climb")}, {CMenu::exit()});

    do
    {
        Console::printLn("You enter through the only enty, and the inside is totally boring. You will have to climb "
                         "the tower, up to the top. There seems to be no elevator. Fun! Fun! Fun!");

        input = menu.execute();
        if (input.key == 'c')
        {
            climb();
            if (CGameManagement::getPlayerInstance()->isDead())
            {
                return;
            }
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
        if (CGameManagement::getPlayerInstance()->isDead())
        {
            return;
        }

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
            if (CGameManagement::getPlayerInstance()->isDead())
            {
                return;
            }
        }
    }
}

void CBlackIvoryTower::executeTopOffice()
{
    printHeader(BlackIvoryTowerRessources::towerHeight);
    Console::printLn("Finally, the top floor!");
    Console::printLn(
        std::format("The winding stair case seemed like forever! This is the office in the top floor. Obviously, the "
                    "office of {}. It is stuffed with books and papers, there is a big desk in front of the window. "
                    "Looks like a mages chamber. Or the chamber of a master beurocrat.",
                    Ressources::Game::mobi()));
    Console::br();

    if (!_isOpen)
    {
        Console::printLn(std::format("{} is here, and does not look very amused. \"How dare you, coming here, and kill "
                                     "all my {}?\", she asks, and without waiting for an answer, she attacks.",
                                     Ressources::Game::mobi(),
                                     BlackIvoryTowerRessources::lunatics()));
        Console::br();
        Console::confirmToContinue();

        CDarkMobi mobi;
        mobi.printBossBattleHeader();
        CBattle battle(&mobi);
        battle.fight();

        if (CGameManagement::getPlayerInstance()->isDead())
        {
            return;
        }

        _isOpen = true;
        CGameManagement::getProgressionInstance()->reportModuleFinished(BlackIvoryTowerRessources::moduleName());
        Console::printLn(std::format(
            "You task was to talk to {0}, not to kill her, so you let her live, and you start talking. As "
            "expected, {0} is not very excited about the death of her {1}, but she is a former member of "
            "the rebellion, and still well-disposed towards {2} and {3}, since they have a common past together",
            Ressources::Game::mobi(),
            BlackIvoryTowerRessources::lunatics(),
            Ressources::Game::fiego(),
            Ressources::Game::brock()));
        Console::printLn(std::format(
            "She also knows about {} and {}, Both accompanied her, when she left the rebellion, but she also hat to "
            "part ways, since the crying became too much even for her. \"You met them?\" she asks \"Well, yes, I met "
            "them is your cautious answer, knowing the direction this talk is taking. \"How are they?\", you decide to "
            "stick with the answer that worked before: \"Well, they stopped crying.\" {} looks at you, as if she just "
            "witnessed you, hanging up the moon: \"You must truely be the chosen one!\"",
            Ressources::Game::bimmelchen(),
            Ressources::Game::pimmelchen(),
            Ressources::Game::mobi()));
        Console::printLn(std::format(
            "In the end, she agrees to support the rebellion as much as she can, even though, she will "
            "not become a member again, for the price of some {}sand{}wiches{}. You did not realize, but your "
            "sandwiches start to become a thing in the land.",
            CC::fgGreen(),
            CC::fgLightYellow(),
            CC::ccReset()));

        Console::confirmToContinue();
        return;
    }
    else
    {
        Console::printLn(std::format("{} is not here right now. probably she is off having some {}sand{}wiches{}. "
                                     "Seems you climbed the stairs for nothing.",
                                     Ressources::Game::mobi(),
                                     CC::fgGreen(),
                                     CC::fgLightYellow(),
                                     CC::ccReset()));
    }
}

void CBlackIvoryTower::executeStairs(const unsigned int stage)
{
    printHeader(stage);

    Console::printLn("Gray brick walls, a stair case up and a stair case down. This floor looks exactly like all the "
                     "other floors. there is no decoration, no tapestry (as you would expect in a building like that, "
                     "and if you would not cout the floors for yourself you would not have the slightest idea, whether "
                     "you are on the 1st, or the 100th floor.");

    if (stage < (BlackIvoryTowerRessources::towerHeight / 5))
    {
        Console::printLn("Looking out of one of the small windows, you can see that you are not very high.");
    }
    else if (stage < (BlackIvoryTowerRessources::towerHeight / 5) * 4)
    {
        Console::printLn(
            std::format("Looking out of one of the small windows, you get a great view over the land. You can see "
                        "forests and mountains, seas and rivers, and far away the towers ot the cathedral of {}",
                        Ressources::Rooms::getCapital().first));
    }
    else
    {
        Console::printLn(
            "Looking out of one of the small windows, you can see that you high up in the sky. there are clouds below "
            "you, and the people are looking like ants (or are that ants, and you are not so very high?).");
    }

    if (_isOpen)
    {
        return;
    }

    switch (Randomizer::getRandom(10))
    {
    case 0:
        Console::printLn("A water bassin, after all those stairs, a cool refreshing drink is exactly the right thing!");
        CGameManagement::getPlayerInstance()->addHp(Randomizer::getRandom(5) + 5);
        break;
    case 1:
        Console::printLn("Wow, you find something usable!");
        CGameManagement::getInventoryInstance()->addShopItem();
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    default:
    {
        Console::printLn(
            std::format("Here we go, One of the {} is guarding this floor. He attacks directly, when he sees you!",
                        BlackIvoryTowerRessources::lunatics()));
        CLunatic lunatic;
        CBattle battle(&lunatic);
        battle.fight();
        if (CGameManagement::getPlayerInstance()->isDead())
        {
            return;
        }
    }
    break;
    }
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
        Console::printLn("Top floor", Console::EAlignment::eCenter);
    }
    else
    {
        Console::printLn(std::format("Floor {}", stage), Console::EAlignment::eCenter);
    }
    Console::br();
}
