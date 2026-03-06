#include "crabbitclearing.h"

#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"
#include "rabbitfarm/crabbitmap.h"
#include "rabbitfarm/items/crabbit.h"
#include "rabbitfarm/items/crabbitfood.h"
#include "rabbitfarm/moduleressources.h"
#include "rabbitfarm/npc/ckatnottingh.h"

CRabbitClearing::CRabbitClearing(CKatNottingH* kat, const CRabbitMap* rabbits) : _kat(kat), _rabbits(rabbits)
{
}

void CRabbitClearing::execute(const std::string_view&)
{
    CEncounter::execute();
    Console::br();
    Console::printLn(tr("A sunny clearing in the middle of a small forest. It is calm and nice here. Some trees and "
                        "bushes, juicy green grass and herbs. a paradise for rabbits. {} would love beeing here.",
                        RabbitFarm::katNottingH()));
    CMenu menu(RabbitFarm::moduleName());
    auto foodAction = menu.createAction({"Gather feed"});
    auto catchAction = menu.createAction({"Catch rabbit"});
    menu.addMenuGroup({foodAction}, {CMenu::exit()});

    CRabbit* rabbit = nullptr;

    auto freeIndex = _rabbits->getRandomFreeIndex();
    if (!CGameManagement::getInventoryInstance()->hasItem(CRabbit::rabbitFilter()) && freeIndex.has_value())
    {

        rabbit = new CRabbit(*freeIndex);

        Console::br();
        Console::printLn(tr("On the clearing, you can see a rabbit, he seems like a very special one. Your rabbit "
                            "expertise tells you, that this particular specimen is a {}.",
                            rabbit->name()));
        Console::printLn(tr("It feels mayestic to see such a rare animal in its natural hebitat. This must be one of "
                            "{}s rabbits. She would probably really like to get this one back.",
                            RabbitFarm::katNottingH()));
        Console::printLn(tr("Also {} would like to have it. The mony is good for sure, but {} would not like that. "
                            "But, Will she ever notice?",
                            RabbitFarm::slasher(),
                            RabbitFarm::katNottingH()));
        menu.addMenuGroup({catchAction});
    }

    const auto input = menu.execute();

    if (rabbit != nullptr && input == CMenu::exit())
    {
        Console::br();
        Console::printLn(
            tr("{} would really like to have this one back. You are sure she knows.", RabbitFarm::katNottingH()));
        _kat->addSympathy(-1);
    }
    if (rabbit != nullptr && input != catchAction)
    {
        delete rabbit;
    }

    if (input == catchAction)
    {
        Console::br();
        Console::printLn(
            tr("Just like the hero you are, you jump towards the {}, trying to cathch it. It takes a few attempts, and "
               "the one or another puddle hits you bit in the end, it is just a rabbit and no match for you.",
               rabbit->name()));
        CGameManagement::getInventoryInstance()->addItem(rabbit);
    }
    if (input == foodAction)
    {
        Console::br();
        Console::printLn(tr(
            "A little feed for thw rabbits cannot hurt. Even if you do not bring a rabbit, you can bring some feed for "
            "the little guys. {} will like it.",
            RabbitFarm::katNottingH()));
        Console::printLn(tr("You collect a big bag of grass, herbs and even some clover."));
        CGameManagement::getInventoryInstance()->addItem(new CRabbitFood);
    }
}

unsigned int CRabbitClearing::encounterChance(const EEncounterType& tp, const std::string_view&) const
{
    if (tp == EEncounterType::eField)
    {
        return 5;
    }
    return 0;
}

std::string CRabbitClearing::name() const
{
    return tr("Sunny Clearing");
}

std::string CRabbitClearing::moduleName() const
{
    return RabbitFarm::moduleName();
}

std::string CRabbitClearing::translatorObjectName() const
{
    return std::string(TagNames::RabbitFarm::rabbitClearingEncounter);
}
