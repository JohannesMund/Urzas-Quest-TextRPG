#include "claylaencounter.h"
#include "cgamemanagement.h"
#include "claylatask.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "moduleressources.h"

#include <format>

CLaylaEncounter::CLaylaEncounter()
{
    _isSingleExecution = true;
    _type = CEncounter::eField;
}

void CLaylaEncounter::execute(const std::string_view& moduleName)
{
    Console::printLn("Next to the road, there is a broken cart, probably involved into a heavy accident. An injured, "
                     "armored guard lies there and needs help.");
    Console::br();
    Console::printLn("Do you want to help?");

    CMenu menu;
    menu.addMenuGroup({menu.createAction("Help"), menu.createAction("Ignore")});
    if (menu.execute().key == 'i')
    {
        Console::printLn("You dont feel very heroic today. Maybe another time, you are sure, you will see this exact "
                         "scene again (especially, if this event is story-relevant.");
        return;
    }

    Console::printLn("Well, time for work, you go to the crashed cart, and help the injured guard. His injuries are "
                     "not only from the crash, this guy has been heavily beaten up.");
    Console::printLn(std::format(
        "You ask him what happened, and he tells you, that he was guaring {} and they got ambushed by highwaymen. The "
        "usual story, log on the street, cart crashes, guard is beaten up, princess is kidnapped.",
        Ressources::Game::princessLayla()));
    Console::printLn("Since this guy is seriously injured and the princess should be rescued soon (is she hot?) it is "
                     "up to you, to do the job.");
    Console::br();
    Console::printLn("Will you do it?");

    menu.clear();
    menu.addMenuGroup({menu.createAction("Hell Yeah!"), menu.createAction("No")});
    if (menu.execute().key == 'n')
    {
        Console::printLn("You dont feel very heroic today, and usually, princesses in need are not very hot. Maybe "
                         "another time, you are sure, you will see this exact "
                         "scene again (especially, if this event is story-relevant.");
        return;
    }

    Console::printLn("This a job for... ok, you need a name, it is a job for you, lets go.");

    CGameManagement::getInstance()->placeTaskOnField(new CLaylaTask());

    _hasBeenExecuted = true;
}

unsigned int CLaylaEncounter::encounterChance(const EEncounterType& tp, const std::string_view& moduleName) const
{
    return 5;
}

std::string CLaylaEncounter::name() const
{
    return std::format("{1}Kidnapped {0}P{1}rincess{2}", CC::fgLightMagenta(), CC::fgLightBlue(), CC::ccReset());
}

std::string CLaylaEncounter::moduleName() const
{
    return LaylaRessources::moduleName();
}
