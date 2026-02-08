#include "cfindguardstask.h"

#include "cbattle.h"
#include "ccapital.h"
#include "cgamemanagement.h"
#include "cleilarescuecapitaltask.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"

#include "leilarescue/companions/cguardcompanion.h"
#include "leilarescue/enemies/ccannibalhorde.h"
#include "leilarescue/enemies/cvenusflytrap.h"
#include "leilarescue/items/cguardstuff.h"
#include "leilarescue/moduleressources.h"

#include <cmath>
#include <format>

CFindGuardsTask::CFindGuardsTask(const unsigned int number) :
    CTask(TagNames::LeilaRescue::findGuards),
    _currentStep(number)
{
}

void CFindGuardsTask::execute()
{
    switch (_currentStep)
    {
    case 0:
    default:
        findFirstGuard();
        break;
    case 1:
        rescueGuardFromMafia();
        break;
    case 2:
        fightCannibalHorde();
        break;
    case 3:
        collectStuff();
        break;
    case 4:
        fightBossMonster();
        break;
    }
}

void CFindGuardsTask::finishTask()
{
    _isFinished = true;
    if (_currentStep < _maxNumber)
    {
        CGameManagement::getInstance()->placeTaskOnField(new CFindGuardsTask(_currentStep + 1));
    }
    else
    {
        Console::printLn(std::format(
            "And with this, you managed to rescue all {} guards. The guys instantly start discussing how to "
            "approach the dungeon beneath the capital. So, up and away, time to head to the capital and  rescue {}.",
            _maxNumber,
            Ressources::Game::leila()));
        CGameManagement::getInstance()->placeTask(new CLeilaRescueCapitalTask(), CCapital::townFilter());
    }
}

nlohmann::json CFindGuardsTask::save() const
{
    auto o = CTask::save();
    o[TagNames::LeilaRescue::stuffCollectionStarted] = _stuffCollectionStarted;
    o[TagNames::LeilaRescue::mafiaMoney] = _mafiaMoney;
    o[TagNames::LeilaRescue::findGuardsStep] = _currentStep;
    o[TagNames::LeilaRescue::lootItemGeneratorRegistered] = _lootItemGeneratorReguistered;
    return o;
}

void CFindGuardsTask::load(const nlohmann::json& json)
{
    _currentStep = json.value<unsigned int>(TagNames::LeilaRescue::findGuardsStep, 0);
    _mafiaMoney = json.value<unsigned int>(TagNames::LeilaRescue::mafiaMoney, 0);
    _stuffCollectionStarted = json.value<bool>(TagNames::LeilaRescue::stuffCollectionStarted, false);
    _lootItemGeneratorReguistered = json.value<bool>(TagNames::LeilaRescue::lootItemGeneratorRegistered, false);

    if (_lootItemGeneratorReguistered)
    {
        registerLootItemGenerator();
    }
    CTask::load(json);
}

void CFindGuardsTask::findFirstGuard()
{
    Console::printLn(std::format(
        "You find the first of the guards, you know the guy, you treated his wounds after his first beat-up by the "
        "rebellion. His name is {}. He recognizes you and after some short explainations, he agrees to help.",
        nameOfCurrentGuard()));

    Console::printLn(std::format("But unfortunately, he and the other guards scattered and lost each other. Most "
                                 "probaby the others are in danger, not only are they bad at their jobs as guards, but "
                                 "they are also not used to to wild live outside the capital. You will have to find "
                                 "all {}, and together, they will come up with a plan how to get into the dungeon.",
                                 _maxNumber));

    CGameManagement::getPlayerInstance()->addSupportCompanion(new CGuardCompanion(nameOfCurrentGuard()));
    finishTask();
}

void CFindGuardsTask::rescueGuardFromMafia()
{
    if (_mafiaMoney == _mafiaStartingMoney)
    {
        Console::printLn(

            "This one really put himself into he hell of a mess. he is surrounded by several heavily armed "
            "mafia dudes, lead by the boss dude, nobody is looking happy, espesially not the guard. It seems to be "
            "about money. it s always about monay. Looking at the number of mafia dudes and their weapons,  attacking "
            "is not an option, especially, if you want to get the guard out there alive, or at least in one piece.");
    }
    else
    {
        Console::printLn(
            "Not much has changed in the scene, since last time. Only the mafia bookkeper dude is fiddeling around "
            "with his abacus, and you are sure, the the price to free the guard they asked last time is no longer "
            "valid.");
    }

    if (_mafiaMoney < _maxMafiaMoney)
    {
        _mafiaMoney += std::ceil((_mafiaMoney * _mafiaIntrest) / 100);
    }

    Console::br();
    Console::printLn(
        "The Mafia Boss surveys you with is sharp looks: \"So, you are here to get this guy out? This "
        "will be a problem. This guy owes us money. Much money. But i think i can make you an offer, you cannot "
        "refuse.\" He glances at the bookkeper dude. \"Tell our businney partner, how much does his life cost?\"");
    Console::printLn(
        std::format("The bookkeeper dude looks at his abacus and tells you the amount: \"Including "
                    "intrest, special intrest, delay intrest, and special delay inrest, it is {}{} Gold{}.\"",
                    CC::fgYellow(),
                    _mafiaMoney,
                    CC::ccReset()));

    CMenu menu(LeilaRescue::moduleName());
    auto pay = menu.createShopAction({"Pay the dude", 'G'}, _mafiaMoney);
    if (CGameManagement::getPlayerInstance()->gold() >= (int)_mafiaMoney)
    {
        Console::printLn("A lot of money for such a mess of a guy. But... you need his help.");
        menu.addMenuGroup({pay}, {CMenu::exit()});
    }
    else
    {
        Console::printLn(
            "This is a lot of money! Too much, you just dont have enough. Looking into the eyes of the guard, you see "
            "his desperation grow, and his hope shrink. You almost feel sorry for that guy.");
        menu.addMenuGroup({}, {CMenu::exit()});
    }
    if (menu.execute() == pay)
    {
        Console::printLn(std::format(
            "Ok, time to play it cool. You grab your money bag an throw {}{} Gold{} on the table. the bookkeeper dude "
            "looks suspiciously and counts the money. Twice. This takes like ages, but in the end he nods to his boss.",
            CC::fgYellow(),
            _mafiaMoney,
            CC::ccReset()));
        Console::printLn("The messed up guard looks relieved as the mafia dudes set him free. you grab him and leave.");
        CGameManagement::getPlayerInstance()->spendGold(_mafiaMoney);
        CGameManagement::getPlayerInstance()->addSupportCompanion(new CGuardCompanion(nameOfCurrentGuard()));

        finishTask();
        return;
    }

    Console::printLn(std::format(
        "Not this time. You will have to come back. Or maybe not. Maybe there is another way to rescue {0}. Oh please, "
        "let there be another way to rescue {0}! The probably is no other way to rescue {0}",
        Ressources::Game::princessLeila()));
}

void CFindGuardsTask::fightBossMonster()
{
    CVenusFlyTrap boss;
    Console::printLn(
        "You are surprised, no, shocked, SCHOCKED! to find the next guard, and see that, and more important, how "
        "he managed to get himself into trouble.");
    Console::printLn(std::format("{} has been caught by a gigantic {}. The guard hangs crossways in the mouth of the "
                                 "huge, man-eating plant. The plant chews on him, only struggeling with his armor.",
                                 nameOfCurrentGuard(),
                                 boss.name()));
    Console::printLn(
        std::format("Your memory seems to be awesomne. you still remember all of the guards names. Also, the plant "
                    "looks familiar, When you where a kid, you had a tiny {}. Your Grampa baught it in a little shop "
                    "of horrors. You loved the tiny plant. You used to call it \"Flea-eater\". Eventually, you set "
                    "them free, because wild man-eating plants must be free.",
                    boss.name()));
    Console::printLn("But seriously, is that really \"Flea-eater\"?");

    CMenu menu(LeilaRescue::moduleName());
    CMenuAction checkAction = menu.createAction({"Check"});
    CMenuAction retreatAction = menu.createAction({"Retreat"});
    menu.addMenuGroup({checkAction, retreatAction});
    Console::br();

    if (menu.execute() == retreatAction)
    {
        Console::printLn("Probably it is not. And you don't want to risk a fight right now. Guards Armors are sturdy, "
                         "even for such a big monster. This leaves you the time for more preparation.");
        Console::confirmToContinue();
        return;
    }

    Console::printLn(std::format("You approch the giant plant. {}\"Flea-eater? Is that you?\", you ask hopefully, "
                                 "excited to see your old friend again.",
                                 CC::bgLightGreen(),
                                 CC::ccReset()));
    Console::printLn("It is not!");
    Console::printLn("The plant drops its food, and attacks you.");
    CBattle battle(&boss);
    battle.fight();

    Console::printLn("This has not been your old friend. You remember that he did not grow very large, after you set "
                     "him free. Also, you might have forgotten to give him water. And stepped on him several times. So "
                     "no, this was surely not him.");
    Console::printLn("At least, you managed to free another guard.");
    CGameManagement::getPlayerInstance()->addSupportCompanion(new CGuardCompanion(nameOfCurrentGuard()));

    finishTask();
}

void CFindGuardsTask::collectStuff()
{
    const auto listMissingParts = []()
    {
        const auto missing = CGuardStuff::listMissingParts();
        for (const auto& i : missing)
        {
            Console::printLn(std::format("My {}", i));
        }
    };

    if (_stuffCollectionStarted == false)
    {
        Console::printLn(std::format(
            "This guy, {}, seems to be easy. At least, he did not get himself into trouble, like the others. But also, "
            "he completely quit with beeing a guard, throwing away all of his precius guard insignia.",
            nameOfCurrentGuard()));
        Console::printLn(std::format("As with the others, {} is willing to help you, but he can't without his stuff, "
                                     "so you will have to find his guard-stuff.",
                                     nameOfCurrentGuard()));

        registerLootItemGenerator();
        _stuffCollectionStarted = true;

        Console::br();
        Console::printLn("What items he did throw away, you ask?");
        listMissingParts();
    }
    else
    {
        Console::printLn(std::format("You find {} where you left him. Relaxed, sitting under a tree, and waiting for "
                                     "you, bringing him his stuff.",
                                     nameOfCurrentGuard()));
        Console::br();
        if (CGuardStuff::hasAll())
        {
            Console::printLn(std::format("And this time, you have everything. {} is excited to have his precious "
                                         "guard-junk back. He packs his stuff and gets ready to follow you.",
                                         nameOfCurrentGuard()));

            CGameManagement::getPlayerInstance()->addSupportCompanion(new CGuardCompanion(nameOfCurrentGuard()));
            finishTask();

            for (auto i : CGuardStuff::partIterator())
            {
                if (CGuardStuff::has(i))
                {
                    CGameManagement::getInventoryInstance()->removeItem(CGuardStuff::nameForPart(i));
                }
            }

            unRegisterLootItemGenerator();
        }
        else
        {
            Console::printLn(
                std::format("But still, there are things missing. {} still needs some items to be ready to follow you.",
                            nameOfCurrentGuard()));
            listMissingParts();
        }
    }
}

void CFindGuardsTask::registerLootItemGenerator()
{
    CGameManagement::getItemFactoryInstance()->registerLootItemGenerator(
        LeilaRescue::moduleName(), []() { return new CGuardStuff(); }, 50);
    _lootItemGeneratorReguistered = true;
}

void CFindGuardsTask::unRegisterLootItemGenerator()
{
    CGameManagement::getItemFactoryInstance()->unregisterLootItemGeneratorByName(LeilaRescue::moduleName());
    _lootItemGeneratorReguistered = false;
}

std::string CFindGuardsTask::nameOfCurrentGuard() const
{

    switch (_currentStep)
    {
    case 0:
        return Ressources::Game::bimmel();
        break;
    case 1:
        return Ressources::Game::bommel();
        break;
    case 2:
        return Ressources::Game::piefke();
        break;
    case 3:
        return Ressources::Game::schniefke();
        break;
    case 4:
        return Ressources::Game::horst();
        break;
    default:
        return "By the way, who is this guy???";
    }
    return std::string();
}

void CFindGuardsTask::fightCannibalHorde()
{
    Console::printLn(std::format(
        "You find this guard, tied to a stick that hangs over a big fire. You recognize this guy, as you alredy fought "
        "him. His name is {} and he seems to be in big trouble. A lot of savage people, with little bones "
        "tied in their hairs are standing around the fire holding simple wooden plates and forks. You seem to have "
        "discovered a rare, savage tribe of cannibals.",
        nameOfCurrentGuard()));
    Console::printLn(
        "You find this guard, tied to a stick that hangs over a big fire. A lot of savaga people, with little bones "
        "tied in their hairs are standing around the fire holding simple wooden plates and forks. You seem to have "
        "discovered a rare, savage trive of cannibals.");

    Console::printLn("It is already smelling like bacon, so you should hurry, if you want to rescue this guard alive.");

    CMenu menu(LeilaRescue::moduleName());
    CMenuAction attackAction = menu.createAction({"Attack"});
    CMenuAction retreatAction = menu.createAction({"Retreat"});

    menu.addMenuGroup({attackAction, retreatAction});

    if (menu.execute() == retreatAction)
    {

        Console::printLn(
            std::format("There are many cannibals. And you are alone. {} is a big guy, it will take a while "
                        "until he is well done. You should have the time for more preparations. After all, he still is "
                        "a city guard and can very well look after himself.",
                        nameOfCurrentGuard()));
        Console::confirmToContinue();
        return;
    }

    CCannibalHorde horde;
    CBattle battle(&horde);
    battle.fight();

    Console::printLn(
        "Your second genocide. Again, while rescuing the same woman. Well, genocides are daily business for "
        "adventuerers / heros like you. And all genocides where for the greater good.");
    Console::printLn("Of course, if genocides are not the foundation for a good and healthy relationship "
                     "between hero and princess, what else could be?");

    Console::printLn(std::format("You untie {} and lead him to the others.", nameOfCurrentGuard()));
    CGameManagement::getPlayerInstance()->addSupportCompanion(new CGuardCompanion(nameOfCurrentGuard()));

    finishTask();
}
