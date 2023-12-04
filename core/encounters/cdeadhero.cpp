#include "cdeadhero.h"
#include "cgamemanagement.h"
#include "citemfactory.h"
#include "cmenu.h"
#include "console.h"
#include "ressources.h"

#include <format>

CDeadHero::CDeadHero() : CEncounter()
{
    _isSingleExecution = true;
    _type = CEncounter::eField;
}

void CDeadHero::execute(const std::string_view& moduleName)
{
    CEncounter::execute(moduleName);
    _hasBeenExecuted = true;

    Console::printLn(std::format(
        "Making your way through the world of adventure, you find a body, lying next to a tree. It seems to be a hero, "
        "just like you. He wears the same {} as you, and he wears the same {} as you. But, he was not as lucky as you.",
        Ressources::Items::getRandomEquipmentNamesAndDescription(Ressources::Items::EType::eWeapon,
                                                                 Ressources::Items::EQuality::eJunk)
            .first.at(0),
        Ressources::Items::getRandomEquipmentNamesAndDescription(Ressources::Items::EType::eShield,
                                                                 Ressources::Items::EQuality::eJunk)
            .first.at(0)));
    Console::printLn("He is dead. Definitely dead. He lies in a puddle of his own blood, the limbs broken, all his "
                     "treasure gone (if he even had som treasure at all). All of his treasure?");
    Console::printLn("Maybe, just maybe you should have a look.");
    Console::br();

    CMenu menu;
    menu.addMenuGroup({menu.createAction("Search the body")}, {menu.createAction("Go away")});
    if (menu.execute().key == 'g')
    {
        Console::br();
        Console::printLn(
            "Better safe than sorry is the motto of this adventure. You leave the poor guy be, and leave.");
        Console::printLn("You feel, that this is the last time, you have seen him");
        return;
    }

    Console::br();
    Console::printLn("You approach the body, and one thing is for sure: This guy is dead. The opponent must have had "
                     "enormous claws (or a Nokia 3210). But one thing survived the fight. His shirt seems pretty "
                     "unharmed. It could be very usefull for you too.");
    Console::printLn("You wonder, if you should take it.");

    menu.clear();
    menu.addMenuGroup({menu.createAction("Take t-shirt")}, {menu.createAction("Go away")});
    if (menu.execute().key == 'g')
    {
        Console::br();
        Console::printLn(
            "Better safe than sorry is the motto of this adventure. You leave the poor guy be, and leave.");
        Console::printLn("You feel, that this is the last time, you have seen him");
        return;
    }
    Console::br();
    Console::printLn("Why waste a valuable item, when it can protect you? You take the T-shirt and equip it. You now "
                     "have a shiny new armor to protect you.");

    CGameManagement::getInventoryInstance()->addItem(CGameManagement::getItemFactoryInstance()->makeEquipment(
        Ressources::Items::EType::eArmor, Ressources::Items::EQuality::eJunk));
    Console::br();
}

unsigned int CDeadHero::encounterChance(const EEncounterType&, const std::string_view&) const
{
    return 5;
}

std::string CDeadHero::name() const
{
    return "Dead Hero";
}
