#include "cslasher.h"

#include "../crabbitmap.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "rabbitfarm/ckatnottingh.h"
#include "rabbitfarm/items/crabbit.h"
#include "rabbitfarm/moduleressources.h"
#include "randomizer.h"

CSlasher::CSlasher(CKatNottingH* kat, CRabbitMap* rabbits) :
    CTownModule(RabbitFarm::rabbitHatchName()),
    _kat(kat),
    _rabbits(rabbits)
{
}

void CSlasher::execute()
{
    makeDishOfTheDay();
    CMenuAction input;

    do
    {
        Console::cls();
        Console::printLn(RabbitFarm::slasher(), Console::EAlignment::eCenter);
        Console::printLn(tr("The best rabbit roast since 825 ad. dragonis"), Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(tr("Dish of the day:"), Console::EAlignment::eCenter);
        Console::printLn(std::format("~ {} ~", _dishOfTheDay), Console::EAlignment::eCenter);
        Console::br();

        CMenu::ActionList slasherList;
        CMenu menu(RabbitFarm::moduleName());

        auto eatAction = menu.createShopAction({"Eat Roast"}, RabbitFarm::rabbitRoastPrice());
        if (CGameManagement::getPlayerInstance()->gold() >= RabbitFarm::rabbitRoastPrice())
        {
            slasherList.push_back(eatAction);
        }

        auto rabbitAction = menu.createAction({"Deliver rabbit"});
        if (CGameManagement::getInventoryInstance()->hasItem(CRabbit::rabbitFilter()))
        {
            slasherList.push_back(rabbitAction);
        }

        auto askActionString = tr("Ask about {}", CC::unColorizeString(RabbitFarm::katNottingH()));
        auto askAction = menu.createAction({askActionString});
        menu.addMenuGroup({askAction});
        menu.addMenuGroup(slasherList, {CMenu::exit()});

        input = menu.execute();

        if (input == eatAction)
        {
            eat();
        }
        if (input == rabbitAction)
        {
            deliverRabbit();
        }
        if (input == askAction)
        {
            ask();
        }

    } while (input != CMenu::exit());
}

CMenuAction CSlasher::townModuleNav(CMenu& menu) const
{
    return menu.createAction({CC::unColorizeString(RabbitFarm::slasher()), 'S'}, false);
}

std::string CSlasher::translatorModuleName() const
{
    return RabbitFarm::moduleName();
}

std::string CSlasher::translatorObjectName() const
{
    return std::string(TagNames::RabbitFarm::slasher);
}

void CSlasher::eat()
{
    Console::printLn(tr("{} the chef himself serves you your {}. It is delicious. The rabbit is served plain, without "
                        "side dishes, just a little sauce. It is joicy and tender. A reall delicacy.",
                        RabbitFarm::slasher(),
                        _dishOfTheDay));
    Console::printLn(
        tr("Through the window, you can see {} through the window. She obeserves every bite you take from your dish.",
           RabbitFarm::katNottingH()));
    Console::printLn(tr("Her gaze judges you silently."));

    CGameManagement::getPlayerInstance()->addXp(50 + Randomizer::getRandom(50));
    CGameManagement::getPlayerInstance()->fullHeal();
    _kat->addSympathy(-25);
    Console::confirmToContinue();
}

void CSlasher::deliverRabbit()
{
    auto rabbit = CGameManagement::getInventoryInstance()->getFirstItemByFilter<CRabbit>(CRabbit::rabbitFilter());
    if (!rabbit.has_value())
    {
        Console::printLn(tr("Turns out, you do not have a rabbit. You better go now."));
        return;
    }

    Console::printLn(tr("Your {} looks too delicious to not be a sunday roast. If there is one person in this land, "
                        "who can make a worty dish out of it, that it is {}.",
                        rabbit.value()->name(),
                        RabbitFarm::slasher()));
    Console::printLn(tr("You hand over your rabbit. {} smiles especially evil. You hear a \"{}M{}uahahaha{}\" - sound",
                        RabbitFarm::slasher(),
                        CC::fgRed(),
                        CC::fgBlack(),
                        CC::ccReset()));

    CGameManagement::getPlayerInstance()->gainGold(2500);
    CGameManagement::getPlayerInstance()->addXp(25 + Randomizer::getRandom(250));

    rabbit.value()->roast();
    _rabbits->add(rabbit.value());
    CGameManagement::getInventoryInstance()->removeItem(rabbit.value());

    Console::printLn(tr("Through the window, you can see {}, watching your deal with disgust. You should probably not "
                        "visit her too soon.",
                        RabbitFarm::katNottingH()));
    _kat->addSympathy(-250);
    _kat->breakUp();
    Console::confirmToContinue();
}

void CSlasher::ask()
{
    Console::printLn(
        tr("You ask {} about this strange arrangement. And he eagerly tells you the story.", RabbitFarm::slasher()));
    Console::printLn(tr("Turns out, that his father was a famous chef, and {}s mother a exquisite rabbit breeder.",
                        RabbitFarm::katNottingH()));
    Console::printLn(tr("Together, they built this rabbit roast restaurant with attached rabbit farm. {}s mother bred "
                        "the rabbits, {}s father made the roast. The restaurant was booked months in advance, people "
                        "travelled through the whole country for a delicious sunday rabbit roast.",
                        RabbitFarm::katNottingH(),
                        RabbitFarm::slasher()));
    Console::printLn(tr("When it was the turn of the kids, to take over the businnes, {} had joined the {} crew, a "
                        "radical environmentalist group. She hired a witch, who put a curse on {}. When he takes a "
                        "single rabbit from the hatch, bad things will happen.",
                        RabbitFarm::katNottingH(),
                        RabbitFarm::apple(),
                        RabbitFarm::slasher()));
    Console::printLn(tr("Unfortunately, {} does not want to go into too much detail about the curse."));
    Console::br();
    Console::printLn(
        tr("Important to know is, that the rabbits are gone at the moment. {} has to gather them back. And everybody "
           "else can do so too. He is willing, to pay {}generous amounts of gold{} for a rabbit",
           RabbitFarm::katNottingH(),
           CC::fgYellow(),
           CC::ccReset()));
    Console::confirmToContinue();
}

void CSlasher::makeDishOfTheDay()
{
    _dishOfTheDay = tr("Roasted {}", RabbitFarm::makeRabbitName());
}
