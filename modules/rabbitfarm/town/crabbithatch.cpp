#include "crabbithatch.h"

#include "cgamemanagement.h"
#include "console.h"
#include "rabbitfarm/ckatnottingh.h"
#include "rabbitfarm/crabbitmap.h"
#include "rabbitfarm/encounters/crabbitclearing.h"
#include "rabbitfarm/items/crabbit.h"
#include "rabbitfarm/items/crabbitfood.h"
#include "rabbitfarm/moduleressources.h"
#include "randomizer.h"

#include <nlohmann/json.hpp>

CRabbitHatch::CRabbitHatch(CKatNottingH* kat, CRabbitMap* rabbits) :
    CTownModule(TagNames::RabbitFarm::rabbitFarm),
    _kat(kat),
    _rabbits(rabbits)
{
}

void CRabbitHatch::execute()
{
    makeRabbitOfTheDay();
    CMenuAction input;
    do
    {
        Console::cls();
        Console::printLn(tr("{}s famous rabbit farm", RabbitFarm::katNottingH()), Console::EAlignment::eCenter);
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

        auto donateAction = menu.createAction({"Donate feed"});
        if (CGameManagement::getInventoryInstance()->hasItem(CRabbitFood::rabbitFoodFilter()))
        {
            katList.push_back(donateAction);
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
        if (input == donateAction)
        {
            donate();
        }
        if (input == katAction)
        {
            _kat->interact();
        }
    } while (input != CMenu::exit());
}

CMenuAction CRabbitHatch::townModuleNav(CMenu& menu) const
{
    return menu.createAction({"Rabbit Hatch", 'R'});
}

nlohmann::json CRabbitHatch::save() const
{
    nlohmann::json o;
    o["encounterRegistered"] = _clearingEncounterRegistered;
    return 0;
}

void CRabbitHatch::load(const nlohmann::json& json)
{
    if (json["encounterRegistered"])
    {
        registerEncounter();
    }
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
    Console::cls();
    Console::printLn(
        tr("\"Food for the food god\" you scream while running into the hat, carrying you bag of rabbit feed."));
    Console::printLn(tr("{} looks at you a little confused. Obviously she does not get the reference. Obviously, she "
                        "does not think that you are funny, but that you are  a very very strange man.",
                        RabbitFarm::katNottingH()));
    Console::printLn("But at least, she appreciates your generous food donation.");
    auto items = CGameManagement::getInventoryInstance()->getItemsByFilter(CRabbitFood::rabbitFoodFilter());
    Console::printLn(tr("You put your {} bags of rabbit foot into the donation container.", items.size()));
    _kat->addSympathy(25 * items.size());
    CGameManagement::getInventoryInstance()->removeItem(CRabbitFood::rabbitFoodFilter());
    Console::confirmToContinue();
}

void CRabbitHatch::watch()
{
    CMenuAction input;
    do
    {
        Console::cls();
        Console::printLn("You decide to visit the rabbits.");
        if (_rabbits->countLiving() == 0)
        {
            Console::printLn(tr("It is a sad image, watching this empty rabbit hatch. All rabbits escaped. It will be "
                                "a task for an especially brave and incredibly strong adventurer toget them back."));
            Console::printLn(
                tr("Surely, {} would love this especially brave and incredibly strong adventurer for doing this.",
                   RabbitFarm::katNottingH()));
            Console::printLn(tr("If only, you knew where to find a especially brave and incredibly strong adventurer"));
            registerEncounter();
        }
        else if (_rabbits->countLiving() == CRabbitMap::max())
        {
            Console::printLn(
                tr("All rabbits are found. Most of them are happily jumping around in the hatch. {} Loves it. She "
                   "seems to be much more happy, and much more delighted, since all of her rabbits are back.",
                   RabbitFarm::katNottingH()));
            Console::printLn("ALso, you feek, that she sees you as a really brave and incredibly strong hero.");
        }
        else if (_rabbits->count() == CRabbitMap::max())
        {
            Console::printLn(tr("All rabbits are found. Most of them are happily jumping around in the hatch. Some are "
                                "more... on the delicious side of things."));
        }
        else
        {
            Console::printLn(tr("There are rabbits, but there are still a lot of rabbits out there, hungry, freezing, "
                                "alone... {} looks at you expectantly"));
        }

        Console::br();
        _rabbits->print();
        Console::br();

        CMenu menu;
        auto watchAction = menu.createAction({"Watch"});
        menu.addMenuGroup({watchAction}, {CMenu::exit()});
        input = menu.execute();

        if (input == watchAction)
        {
            watchOneRabbit();
        }
    } while (input != CMenu::exit());
}

void CRabbitHatch::ask()
{
    Console::cls();
    Console::printLn(tr("You ask {} about this strange arrangement. And he eagerly tells you the story.",
                        RabbitFarm::katNottingH()));
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
    Console::confirmToContinue();
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
    if (!item.has_value())
    {
        Console::printLn(tr("The rabbit is dead, lets cover up this quickly."));
        return;
    }

    auto rabbit = dynamic_cast<CRabbit*>(*item);

    Console::printLn(tr("You remember, that you found one of the rabbits. Proudly, you reach under your {} and present "
                        "your finding. It is a:",
                        CGameManagement::getPlayerInstance()->armorName()));

    Console::br();
    Console::printLn(rabbit->name(), Console::EAlignment::eCenter);
    Console::printLn(rabbit->description(), Console::EAlignment::eCenter);
    Console::br();

    Console::printLn(tr("And this rabbit is definitely not burmt. You realize, that this was oddly specific, but you "
                        "can see the smile on {}s face. She is very happy to get this rabbit back.",
                        RabbitFarm::katNottingH()));

    _rabbits->add(rabbit);
    _kat->addSympathy(50);
    Console::confirmToContinue();
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
            Console::printLn(tr("{} does not like that", RabbitFarm::katNottingH()));
            _kat->addSympathy(-1);
        }
    }
}

void CRabbitHatch::registerEncounter()
{
    if (!_clearingEncounterRegistered)
    {
        CGameManagement::getInstance()->registerEncounter(new CRabbitClearing(_kat, _rabbits));
        _clearingEncounterRegistered = true;
    }
}

void CRabbitHatch::makeRabbitOfTheDay()
{
    _rabbitOfTheDay = RabbitFarm::makeRabbitName();
}
