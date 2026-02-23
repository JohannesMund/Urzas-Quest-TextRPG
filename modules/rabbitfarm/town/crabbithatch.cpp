#include "crabbithatch.h"

#include "../crabbitmap.h"
#include "cgamemanagement.h"
#include "console.h"
#include "rabbitfarm/ckatnothingh.h"
#include "rabbitfarm/items/crabbit.h"
#include "rabbitfarm/moduleressources.h"
#include "randomizer.h"

CRabbitHatch::CRabbitHatch(CKatNothingH* kat, CRabbitMap* rabbits) :
    CTownModule(TagNames::RabbitFarm::rabbitFarm),
    _kat(kat),
    _rabbits(rabbits)
{
}

void CRabbitHatch::execute()
{
    makeRabbitOfTheDay();
    CGameManagement::getInventoryInstance()->addItem(new CRabbit(Randomizer::getRandom(150)));

    CMenuAction input;
    do
    {
        Console::cls();
        Console::printLn(tr("{}s famous rabbit farm", RabbitFarm::katNothingH()), Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(tr("Rabbit of the day:"), Console::EAlignment::eCenter);
        Console::printLn(std::format("~ {} ~", _rabbitOfTheDay), Console::EAlignment::eCenter);
        Console::br();

        CMenu::ActionList katList;
        CMenu menu(RabbitFarm::moduleName());

        auto askActionString = tr("Ask about {}", CC::unColorizeString(RabbitFarm::slasher()));
        auto askAction = menu.createAction({askActionString});

        auto watchAction = menu.createAction({"Watch rabbits"});
        katList.push_back(watchAction);

        auto rabbitAction = menu.createAction({"Deliver rabbit"});
        if (CGameManagement::getInventoryInstance()->hasItem(CRabbit::rabbitFilter()))
        {
            katList.push_back(rabbitAction);
        }
        auto katAction = _kat->npcNav(menu);
        menu.addMenuGroup({askAction}, {katAction});
        menu.addMenuGroup(katList, {CMenu::exit()});

        input = menu.execute();

        if (input == rabbitAction)
        {
            deliverRabbit();
        }
        if (input == askAction)
        {
            ask();
        }
        if (input == watchAction)
        {
            watch();
        }
        if (input == katAction)
        {
            _kat->interact();
        }
        if (input != CMenu::exit())
        {
            Console::confirmToContinue();
        }

    } while (input != CMenu::exit());
}

CMenuAction CRabbitHatch::townModuleNav(CMenu& menu) const
{
    return menu.createAction({"Rabbit Hatch", 'R'});
}

std::string CRabbitHatch::translatorModuleName() const
{
    return std::string(RabbitFarm::moduleName());
}

std::string CRabbitHatch::translatorObjectName() const
{
    return std::string(TagNames::RabbitFarm::rabbitHatch);
}

void CRabbitHatch::donate()
{
}

void CRabbitHatch::watch()
{
    CMenuAction input;
    do
    {
        Console::cls();
        Console::printLn("You decide to visit the rabbits.");
        Console::br();
        _rabbits->print(); /* code */
        Console::br();

        CMenu menu;
        auto watchAction = menu.createAction({"Watch"});
        menu.addMenuGroup({watchAction}, {CMenu::exit()});
        input = menu.execute();

        if (input == watchAction)
        {
            watchOneRabbit();
        }

    } while (input == CMenu::exit());
}

void CRabbitHatch::ask()
{
    Console::printLn(tr("You ask {} about this strange arrangement. And he eagerly tells you the story.",
                        RabbitFarm::katNothingH()));
    Console::printLn(tr("Apperently, her mother and {}s father build all of that.", RabbitFarm::slasher()));
    Console::printLn(tr("When she took over from her mother, she decided to continue the breeding of rabbits, but "
                        "protect them, rather than allowimg {} to cook them.",
                        RabbitFarm::slasher()));
    Console::printLn(tr("A nice environmentalist witch put a curse on {}, so whenever he tries to get a rabbit from "
                        "the hatch, {}lightning will strike him while taking a dump{}.",
                        RabbitFarm::slasher(),
                        CC::fgCyan(),
                        CC::ccReset()));
    Console::printLn(tr("In return, {} hired some dude, who let all of her rabbits free. She tries to find them "
                        "desperately but she surely needs help, finding all of the {}{}{} rabbits. She cannot pay you "
                        "much, but turns out that the way into the heart of this lady is through the rabbits.",
                        RabbitFarm::slasher(),
                        CC::fgRed(),
                        _rabbits->max(),
                        CC::ccReset()));
    Console::br();
}

void CRabbitHatch::deliverRabbit()
{
    auto rabbits = CGameManagement::getInventoryInstance()->getItemsByFilter(CRabbit::rabbitFilter());
    if (!rabbits.size())
    {
        Console::printLn(tr("Turns out, you do not have a rabbit. You better go now."));
        return;
    }

    auto item = CGameManagement::getInventoryInstance()->takeItem(rabbits.at(0));
    if (item.has_value())
    {
        auto rabbit = dynamic_cast<CRabbit*>(*item);
        _rabbits->add(rabbit);
    }
    _kat->addSympathy(50);
}

void CRabbitHatch::watchOneRabbit()
{
    Console::printLn(tr("You want to have a look at the rabbit with the number:"));
    auto input = Console::getNumberInputWithEcho(CRabbitMap::min(), CRabbitMap::max());
    if (input.has_value())
    {
        auto r = _rabbits->get(*input);

        Console::br();
        if (r == nullptr)
        {
            Console::printLn(tr("The rabbit with the number {} has not been found yet.", *input),
                             Console::EAlignment::eCenter);
            return;
        }
        Console::printLn(r->name(), Console::EAlignment::eCenter);
        Console::printLn(r->description(), Console::EAlignment::eCenter);

        Console::br();
        if (r->isRoasted())
        {
            Console::printLn(tr("Well, you are pretty sure, {} did an awesomne job to make the best roast he could",
                                RabbitFarm::slasher()));
            Console::printLn(tr("{} does not like that", RabbitFarm::katNothingH()));
            _kat->addSympathy(-1);
        }
    }
    Console::confirmToContinue();
}

void CRabbitHatch::makeRabbitOfTheDay()
{
    _rabbitOfTheDay = RabbitFarm::makeRabbitName();
}
