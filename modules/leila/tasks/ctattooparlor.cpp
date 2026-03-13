#include "ctattooparlor.h"

#include "cgamemanagement.h"
#include "cmenu.h"
#include "cnpc.h"
#include "colorize.h"
#include "console.h"
#include "leila/moduleressources.h"

CTattooParlor::CTattooParlor() : CTask(Leila::moduleName())
{
    _isAutoExecute = true;
}

void CTattooParlor::execute()
{
    Console::printLn(tr("As you approach a clearing, you see a {}black tent{} set up on it. There is a wooden sign, "
                        "hand painted with a beautiful, hand-written logo:",
                        CC::fgBlack(),
                        CC::ccReset()));
    Console::printLn(Leila::inkystattooParlor(), Console::EAlignment::eCenter);
    Console::printLn(tr("You do not question the fact, that there is a mere tent, wandering around the world, doing "
                        "tattoos. You also do not ask the question what this means towards questions like hygiene or "
                        "quality. You just ask the question whether you want to update your tattoos."));
    Console::br();

    CMenu menu(Leila::moduleName());
    auto tattooAction = menu.createAction({"Enter", 'E'});
    menu.addMenuGroup({tattooAction}, {CMenu::exit()});

    if (menu.execute() == tattooAction)
    {
        tattooParlor();
        Console::confirmToContinue();
    }
    else
    {
        Console::printLn(tr("Maybe not today. This is too shady."));
    }
}

bool CTattooParlor::isMovable() const
{
    return true;
}

char CTattooParlor::mapSymbol() const
{
    return '+';
}

void CTattooParlor::tattooParlor()
{
    Console::cls();
    Console::printLn(tr(
        "Inside the {}tent{} everything looks like you would expect from a tattoo parlor, even though the only other "
        "tattoo parlor you have seen, well you have not really seen. You memories are blurry, at best.",
        CC::fgBlack(),
        CC::ccReset()));
    Console::printLn(tr("On the other hand, the looks of {} surprise you. You expected a fully tattooed, grim dark "
                        "sailor dude, you meet with a guy made out of ink. Not painted with ink, Made out of ink. Like "
                        "some kind of Ink-elemental... With... needle claws... Very trustworthy.",
                        Leila::inky()));
    Console::printLn(tr("tattoos became a thing for you just recently. So together with {}, you take a look down your "
                        "arm and see your history of tattoos:",
                        Leila::inky()));
    printTattoos();
    Console::printLn("You wonder whether it is time to get rid of those.");

    CMenu menu(Leila::moduleName());
    auto tattooAction = menu.createAction({"Ask for removal", 'A'});
    menu.addMenuGroup({tattooAction}, {CMenu::exit()});

    if (menu.execute() == tattooAction)
    {
        askForRemoval();
    }
    else
    {
        Console::printLn(tr("Maybe not today. You decide to stick with what you have."));
    }
}

void CTattooParlor::askForRemoval()
{
    Console::cls();
    Console::printLn(tr("It is time to clean this mess up. You ask {} to remove your tattoos.", Leila::inky()));
    Console::printLn(tr("{} again takes a very close look, and shakes his head. Removal will not be an option. What he "
                        "can offer is a cover up.",
                        Leila::inky()));
    Console::br();
    CMenu menu(Leila::moduleName());
    auto tattooAction = menu.createAction({"Do it", 'D'});
    menu.addMenuGroup({tattooAction}, {CMenu::exit()});

    if (menu.execute() == tattooAction)
    {
        coverUp();
    }
    else
    {
        Console::printLn(
            tr("Maybe not today. This whole thing does not look like something you want to do right now."));
    }
}

void CTattooParlor::coverUp()
{
    Console::cls();

    std::string newTattoo = tr("Motor Cycle");

    if (CGameManagement::getPlayerInstance()->hasSignificantOther())
    {
        auto npc = CGameManagement::getPlayerInstance()->signigicantOther();

        if ((npc->tattoo().compare(CGameManagement::getPlayerInstance()->tattoo()) == 0))
        {
            Console::printLn(tr("Yes {} is your {}. Yes the tattoo was meant to think about {}, but you are tired of "
                                "seeing it. It has to go now! Maybe, just maybe, {} will not like it.",
                                npc->name(),
                                npc->girlfriendBoyfriend(),
                                npc->himHer(),
                                npc->heShe()));

            npc->addSympathy(-100);
        }
        else
        {
            Console::printLn(tr("It is finally time, to pay tribute to your relationship to {0}. {1} is your {3}, and "
                                "your arm has to show it. {1} will love it for sure!",
                                npc->name(),
                                npc->heShe(),
                                npc->girlfriendBoyfriend()));
            npc->addSympathy(100);
            newTattoo = npc->tattoo();
        }
    }
    else
    {
        Console::printLn(tr(
            "You do not have a love interest, you do not need a love interest. What are love interests, girlfriends, "
            "boyfriends for anyway? it is time to show that with something that really matters to you."));
    }

    Console::printLn(tr("{} takes his time and thoroughly adds your new tattoo to your arm, while carfully using "
                        "hidden lines and dots to cover the old ones. The new Tatoo now reads:",
                        Leila::inky()));
    CGameManagement::getPlayerInstance()->addtattoo(newTattoo);
    CGameManagement::getPlayerInstance()->addHp(-1);
    Console::printLn(
        tr("The whole procedure hurt and you will probably have some fun with it the next days. Even though this tatoo "
           "has been done with more care and professionality than your first one. You are happy with the result."));
    Console::printLn(tr("But... for how long?"), Console::EAlignment::eCenter);
}
void CTattooParlor::printTattoos()
{
    const auto tattooHistory = *CGameManagement::getPlayerInstance()->tattooHistory();
    for (const auto& tattoo : tattooHistory)
    {
        if (tattoo.compare(tattooHistory.back()) == 0)
        {
            Console::printLn(tattoo, Console::EAlignment::eCenter);
        }
        else
        {
            Console::printLn(std::format("{}{}{}", CC::modStrikeThrough(), tattoo, CC::ccReset()),
                             Console::EAlignment::eCenter);
        }
    }
}
