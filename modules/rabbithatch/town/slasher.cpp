#include "slasher.h"

#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "rabbithatch/ckatnothingh.h"
#include "rabbithatch/items/crabbit.h"
#include "rabbithatch/moduleressources.h"
#include "randomizer.h"

CSlasher::CSlasher(CKatNothingH* kat) : CTownModule(RabbitHatch::rabbitHatchName()), _kat(kat)
{
}

void CSlasher::execute()
{
    makeDishOfTheDay();
    CMenuAction input;

    do
    {
        Console::cls();

        Console::printLn(RabbitHatch::slasher(), Console::EAlignment::eCenter);
        Console::printLn(tr("The best rabbit roast since 825 ad. dragonis"), Console::EAlignment::eCenter);
        Console::br();
        Console::br();
        Console::printLn(tr("Dish of the day:"), Console::EAlignment::eCenter);
        Console::printLn(std::format("~ {} ~", _dishOfTheDay), Console::EAlignment::eCenter);
        Console::br();

        CMenu::ActionList slasherList;
        CMenu menu(RabbitHatch::moduleName());

        auto askActionString = tr("Ask about {}", CC::unColorizeString(RabbitHatch::katNothingH()));
        auto askAction = menu.createAction({askActionString});
        slasherList.push_back(askAction);

        auto eatAction = menu.createShopAction({"Eat Rabbit Roast"}, RabbitHatch::rabbitRoastPrice());
        if (CGameManagement::getPlayerInstance()->gold() >= RabbitHatch::rabbitRoastPrice())
        {
            slasherList.push_back(eatAction);
        }

        auto rabbitAction = menu.createAction({"Deliver a rabbit"});
        if (CGameManagement::getInventoryInstance()->hasItem(CRabbit::rabbitFilter()))
        {
            slasherList.push_back(rabbitAction);
        }

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
    return menu.createAction({CC::unColorizeString(RabbitHatch::slasher())}, false);
}

std::string CSlasher::translatorModuleName() const
{
    return RabbitHatch::moduleName();
}

std::string CSlasher::translatorObjectName() const
{
    return std::string(TagNames::RabbitHatch::slasher);
}

void CSlasher::eat()
{
    Console::printLn(tr("{} the chef himself serves you your {}. It is delicious. The rabbit is served plain, without "
                        "side dishes, just a little sauce. It is joicy and tender. A reall delicacy.",
                        RabbitHatch::slasher(),
                        _dishOfTheDay));
    Console::printLn(
        tr("Through the window, you can see {} through the window. She obeserves every bite you take from your dish.",
           RabbitHatch::katNothingH()));
    Console::printLn(tr("Her gaze judges you silently."));

    CGameManagement::getPlayerInstance()->addXp(50 + Randomizer::getRandom(50));
    CGameManagement::getPlayerInstance()->fullHeal();
    _kat->addSympathy(-25);
}

void CSlasher::deliverRabbit()
{
    auto rabbits = CGameManagement::getInventoryInstance()->getItemsByFilter(CRabbit::rabbitFilter());
    if (!rabbits.size())
    {
        Console::printLn(tr("Turns out, you do not have a rabbit. You better go now."));
        return;
    }

    Console::printLn(tr("Your {} looks too delicious to not be a sunday roast. If there is one person in this land, "
                        "who can make a worty dish out of it, that it is {}.",
                        rabbits.at(0)->name(),
                        RabbitHatch::slasher()));
    Console::printLn(tr("You hand over your rabbit. {} smiles especially evil. You hear a \"{}M{}uahahaha{}\" - sound",
                        RabbitHatch::slasher(),
                        CC::fgRed(),
                        CC::fgBlack(),
                        CC::ccReset()));

    CGameManagement::getPlayerInstance()->gainGold(2500);
    CGameManagement::getPlayerInstance()->addXp(25 + Randomizer::getRandom(250));
    CGameManagement::getInventoryInstance()->removeItem(CRabbit::rabbitFilter());
    _kat->addSympathy(-250);
}

void CSlasher::ask()
{
    Console::printLn(
        tr("You ask {} about this strange arrangement. And he eagerly tells you the story.", RabbitHatch::slasher()));
    Console::printLn(tr("Turns out, that his father was a famous chef, and {}s mother a exquisite rabbit breeder.",
                        RabbitHatch::katNothingH()));
    Console::printLn(tr("Together, they built this rabbit roast restaurant with attached rabbit farm. {}s mother bred "
                        "the rabbits, {}s father made the roast. The restaurant was booked months in advance, people "
                        "travelled through the whole country for a delicious sunday rabbit roast.",
                        RabbitHatch::katNothingH(),
                        RabbitHatch::slasher()));
    Console::printLn(tr("When it was the turn of the kids, to take over the businnes, {} had joined the {} crew, a "
                        "radical environmentalist group. She hired a witch, who put a curse on {}. When he takes a "
                        "single rabbit from the hatch, bad things will happen.",
                        RabbitHatch::katNothingH(),
                        RabbitHatch::apple(),
                        RabbitHatch::slasher()));
    Console::printLn(tr("Unfortunately, {} does not want to go into too much detail about the curse"));
    Console::printLn(tr("But, he tells you, that he is willing to pay generous gold for rabbits."));
}

void CSlasher::makeDishOfTheDay()
{
    _dishOfTheDay = tr("Roasted {}", RabbitHatch::makeRabbitName());
}
