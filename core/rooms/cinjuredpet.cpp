#include "cinjuredpet.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"
#include "ressources.h"

#include <format>

CInjuredPet::CInjuredPet() : CField()
{
    _showInFogOfWar = true;

    _encounterType = CEncounter::EEncounterType::eNone;
    _isRandomTaskPossible = false;
}

void CInjuredPet::execute()
{
    CRoom::execute();

    if (CGameManagement::getCompanionInstance()->hasCompanion())
    {
        Console::br();
        Console::printLn(std::format("With a smile, you remember how you found {} here",
                                     CGameManagement::getCompanionInstance()->name()));
        return;
    }

    if (_petIsDead)
    {
        Console::br();
        Console::printLn(
            std::format("You see the corpse of the {} you left here dying. You feel pitty for the little guy.",
                        CGameManagement::getCompanionInstance()->name()));
        return;
    }

    Console::br();
    Console::printLn("A suspicious noise is coming out of one of the bushes, you should have a look. Or maybe, "
                     "you better be carful and ignore it.");
    Console::hr();

    CMenu menu;
    menu.addMenuGroup({menu.createAction("Look"), menu.createAction("Go away")});
    auto input = menu.execute();
    if (input.key == 'g')
    {
        Console::printLn("Better safe than sorry! You decide to ignore the pittyful screams and leave.");
        Console::printLn("The screams vanish shortly after.");
        _petIsDead = true;
        return;
    }

    Console::br();
    Console::printLn(
        std::format("You follow the sounds, and find a tiny {} lying beneath a bush, desperately looking for help",
                    CGameManagement::getCompanionInstance()->name()));

    Console::hr();

    menu.clear();
    menu.addMenuGroup({menu.createAction("Help"), menu.createAction("Go away")});
    if (menu.execute().key == 'g')
    {
        Console::printLn("Better safe than sorry! You decide to ignore the pittyful little animal and leave.");
        Console::printLn("The screams vanish shortly after.");
        _petIsDead = true;
        return;
    }

    Console::br();
    Console::printLn(std::format("You decide to help the {}. a little water, a bandage for the broken limb and some "
                                 "herbs and soon the little fellow is back on track.",
                                 CGameManagement::getCompanionInstance()->name()));
    Console::printLn(
        std::format("As soon as you leave, you realize, that {} follows you. Looks like, you have found a new friend.",
                    CGameManagement::getCompanionInstance()->name()));
    CGameManagement::getCompanionInstance()->evolve();

    _showInFogOfWar = false;

    _encounterType = CEncounter::EEncounterType::eField;
    _isRandomTaskPossible = true;
}

char CInjuredPet::getMapSymbol() const
{
    if (CGameManagement::getCompanionInstance()->hasCompanion() || _petIsDead)
    {
        return CField::getMapSymbol();
    }

    return '?';
}
