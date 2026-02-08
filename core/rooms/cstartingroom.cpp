#include "cstartingroom.h"
#include "cequipment.h"
#include "cgamemanagement.h"
#include "citemfactory.h"
#include "cmenu.h"
#include "console.h"

#include <format>

CStartingRoom::CStartingRoom() : CField(TagNames::Room::startingRoom)
{
    _encounterType = CEncounter::EEncounterType::eNone;
    _isRandomTaskPossible = false;
}

void CStartingRoom::execute()
{
    if (seen())
    {
        CRoom::execute();
        Console::printLn("You can still see, where you woke up, when you started your adventure,");
        return;
    }

    auto sword = CGameManagement::getItemFactoryInstance()->makeEquipment(Ressources::Items::EType::eWeapon,
                                                                          Ressources::Items::EQuality::eJunk);

    CMenu menu;
    CMenuAction takeAction = menu.createAction({"Take it"});
    CMenuAction leaveAction = menu.createAction({"Leave it"});
    menu.addMenuGroup({takeAction, leaveAction});

    CMenuAction input;

    Console::br();
    Console::printLn("You whake up, somewhere.");
    Console::printLn("You have not the slightest idea, where you are.");
    Console::printLn("You look around, and realize, that you are utterly defenseless. You need something to defend "
                     "yourself. Hidden beneath one of the bushes, you see someting:");
    Console::printLn(sword->description());
    Console::printLn("This seems to be a decent weapom, at least for now.");
    Console::br();

    do
    {
        input = menu.execute();
        if (input == takeAction)
        {
            Console::br();
            Console::printLn(std::format("You take the {} and equip it. It looks good on you.", sword->name()));
            CGameManagement::getInventoryInstance()->addItem(sword);
        }
        else
        {
            Console::br();
            Console::printLn("Your parents always taught you, not to pick up stuff from the ground. Who knows wo owns "
                             "this sword. You leave the Sword where it is and turn around.");
            Console::printLn(
                "Than you start thinking. You are still defenseless. Maybe you should re-think your decision.");
            Console::br();
        }
    } while (input != takeAction);

    auto shield = CGameManagement::getItemFactoryInstance()->makeEquipment(Ressources::Items::EType::eShield,
                                                                           Ressources::Items::EQuality::eJunk);

    Console::br();
    Console::printLn("Having the sword, you look further. You still do not feel like a big, sturdy warrior. "
                     "Something is missing.");
    Console::printLn("Wait, is that...?");
    Console::printLn(shield->description());
    Console::br();

    do
    {
        input = menu.execute();
        if (input == takeAction)
        {
            Console::br();
            Console::printLn(std::format("You take the {} and equip it. Now you feel complete.", shield->name()));
            CGameManagement::getInventoryInstance()->addItem(shield);
        }
        else
        {
            Console::br();
            Console::printLn("Ok, by now, you should have realized, that you will not leave without the shield. Let's "
                             "shorten this, ok?");
            Console::br();
        }
    } while (input != takeAction);

    Console::br();
    Console::printLn(
        "Now, that you are equipped, it is time to start your adventure. You look around where you are and find:");
    Console::br();

    CRoom::execute();

    _encounterType = CEncounter::EEncounterType::eField;
    _isRandomTaskPossible = true;
}

char CStartingRoom::getMapSymbol() const
{
    return '*';
}
