#include "cblackivorytower.h"
#include "cbattle.h"
#include "cdarkmobi.h"
#include "cgamemanagement.h"
#include "cgameprogression.h"
#include "clunatic.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "curzasglasses.h"
#include "moduleressources.h"
#include "randomizer.h"

#include <format>

CBlackIvoryTower::CBlackIvoryTower() : CRoom(TagNames::BlackIvoryTower::blackIvoryTower)
{
    _encounterType = CEncounter::EEncounterType::eNone;
    _isRandomTaskPossible = false;
    _showInFogOfWar = false;
}

void CBlackIvoryTower::execute()
{

    CRoom::execute();

    printHeader(0);
    Console::printLn(std::format("The tower is at least 250 feet hight and {}pich black{}, the walls are plated with "
                                 "something looking like ivory, but since it is black it is probably no ivory. Lets "
                                 "call it black ivory. The top of the tower is high up in the sky.",
                                 CC::fgDarkGray(),
                                 CC::ccReset()));
    Console::br();
    if (!_isOpen)
    {
        CUrzasGlasses glasses;
        Console::printLn(
            "You walk around the tower several time, but there seems to be no entry. You continue to walk and walk "
            "and walk und still walk until you get dizzy and decide, that this tower probably has no entry. Or you "
            "cannot see the entry. If only you had some seeing entries support item...");

        if (!CGameManagement::getInventoryInstance()->hasItem(CItem::nameFilter(glasses.name())))
        {
            Console::confirmToContinue();
            return;
        }
        else
        {

            Console::printLn(std::format(
                "Wait, you have found a seeing support item recently. Maybe it is an seeing entries spoort item. whio "
                "knows? You take {0} out of you pocket and put it onto your nose. You walk around the tower once more, "
                "and e voila, there is an entry! {0} is a seeing entries support item!",
                glasses.name()));
            Console::confirmToContinue();
        }
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
        }
    } while (input != CMenu::exit());
}

std::string CBlackIvoryTower::bgColor() const
{
    return CC::bgWhite();
}

std::string CBlackIvoryTower::fgColor() const
{
    return CC::fgBlack();
}

char CBlackIvoryTower::getMapSymbol() const
{
    return 'I';
}

nlohmann::json CBlackIvoryTower::save() const
{
    auto o = CRoom::save();
    o[TagNames::BlackIvoryTower::isOpen] = _isOpen;
    o[TagNames::BlackIvoryTower::hadADoener] = _hadADoener;
    return o;
}

bool CBlackIvoryTower::load(const nlohmann::json& json)
{
    _isOpen = json.value<bool>(TagNames::BlackIvoryTower::isOpen, false);
    _hadADoener = json.value<bool>(TagNames::BlackIvoryTower::hadADoener, false);
    return CRoom::load(json);
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
    Console::printLn("Finally, the top floor!");
    Console::printLn(
        std::format("The winding stair case seemed like forever! This is the office in the top floor. Obviously, the "
                    "office of {}. It is stuffed with books and papers, there is a big desk in front of the window. "
                    "Looks like a mages chamber. Or the chamber of a master beurocrat.",
                    Ressources::Game::darkMobi()));
    Console::br();

    if (!_isOpen)
    {
        Console::printLn(std::format("{} is here, and does not look very amused. \"How dare you, coming here, and kill "
                                     "all my {}?\", she asks, and without waiting for an answer, she attacks.",
                                     Ressources::Game::darkMobi(),
                                     BlackIvoryTowerRessources::lunatics()));
        Console::br();
        Console::confirmToContinue();

        CDarkMobi darkMobi;
        darkMobi.printBossBattleHeader();
        CBattle battle(&darkMobi);
        battle.fight();

        _isOpen = true;
        CGameManagement::getProgressionInstance()->reportModuleFinished(BlackIvoryTowerRessources::moduleName());
        Console::printLn(std::format(
            "You task was to talk to {0}, not to kill her, so you let her live, and you start talking. As "
            "expected, {0} is not very excited about the death of her {1}, but she is a former member of "
            "the rebellion, and still well-disposed towards {2} and {3}, since they have a common past together",
            Ressources::Game::darkMobi(),
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
            Ressources::Game::darkMobi()));
        Console::printLn(
            std::format("In the end, she agrees to support the rebellion as much as she can, even though, she will "
                        "not become a member again. For now, she will open a döner restaurant in her tower.",
                        CC::fgGreen(),
                        CC::fgLightYellow(),
                        CC::ccReset()));

        Console::confirmToContinue();
        return;
    }
    else
    {
        Console::printLn(
            std::format("{0} is not here right now. probably she is off having some {1}sand{2}wiches{3}. "
                        "But you did not climb the stairs for nothing, as promised, {0} opened a Döner shop here in "
                        "her tower. A big barbecue skewer with a huge chunk of meat is slowly spinning over a fire, it "
                        "smells like barbecue and garlic.",
                        Ressources::Game::darkMobi(),
                        CC::fgGreen(),
                        CC::fgLightYellow(),
                        CC::ccReset()));
        Console::printLn(std::format(
            "Behind the counter is one of {}s {}. This guy looks pretty beaten up, his body is covered with scratches "
            "and wounds, he wears bandages and has a black eye. When he sees you, he looks pretty scared. You cannot "
            "stop thinking, that you have seen him before.",
            Ressources::Game::mobi(),
            BlackIvoryTowerRessources::lunatics()));
        Console::printLn("With fear in his eyes and a shaking voice, he offers you a free döner.");

        CMenu menu;

        menu.addMenuGroup({menu.createAction("Have a Döner", 'H')}, {CMenu::exit()});
        if (menu.execute().key == 'h')
        {
            haveADoener();
        }
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
        if (_isOpen)
        {
            Console::printLn(std::format("{}'s Döner", Ressources::Game::mobi()), Console::EAlignment::eCenter);
            Console::printLn("Einmal essen niemals vergessen", Console::EAlignment::eCenter);
        }
        else
        {
            Console::printLn("Top floor", Console::EAlignment::eCenter);
        }
    }
    else
    {
        Console::printLn(std::format("Floor {}", stage), Console::EAlignment::eCenter);
    }
    Console::br();
}

void CBlackIvoryTower::haveADoener()
{
    Console::printLn(
        std::format("With shaking hands, the {0} cuts open some bread, fills it with fresh-cut meat, vegetables and a "
                    "generous splash of the (as he sais) home made garlic sauce. The {0} tries to act professional, "
                    "but in his eyes, you can see the sheer terror. If only you could remember, why he is so scared of "
                    "you. Probably that is, because you are a friend of his boss.",
                    BlackIvoryTowerRessources::lunatic()));
    if (_hadADoener)
    {
        Console::printLn("You already know what to expect. Döner is great, Döner is tasty and for sure, Döner makes "
                         "you more beautiful.");
        Console::printLn("If only you knew, where the urge to put onions on your head is coming from?");
    }
    else
    {
        Console::printLn(
            std::format("So this is a Döner. It is probably the best thing you have ever eaten. It is savory and "
                        "tasty and the home made garlic sauce tastes like heaven. You quickly think about making "
                        "something similar in your {}sand{}wich{} shop, but decide, that this market belongs to {}. "
                        "You feel a strong urge to put onions on your head, and you are sure, that the onions will "
                        "make you look more beautiful.",
                        CC::fgYellow(),
                        CC::fgGreen(),
                        CC::ccReset(),
                        Ressources::Game::darkMobi()));
        CGameManagement::getPlayerInstance()->addXp(99);
    }

    CGameManagement::getPlayerInstance()->addHp(1);
}
