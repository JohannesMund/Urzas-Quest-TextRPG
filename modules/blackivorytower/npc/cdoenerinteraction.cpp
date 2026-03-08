#include "cdoenerinteraction.h"

#include "blackivorytower/moduleressources.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"

CDoenerInteraction::CDoenerInteraction(CNpc* npc) : CNpcInteraction(npc, BlackIvoryTower::moduleName())
{
    _cooldown = 25;
}

void CDoenerInteraction::executeInteraction()
{
    CNpcInteraction::executeInteraction();
    Console::printLn(
        tr("With shaking hands, the {0} cuts open some bread, fills it with fresh-cut meat, vegetables and a "
           "generous splash of the (as he sais) home made garlic sauce. The {0} tries to act professional, "
           "but in his eyes, you can see the sheer terror. If only you could remember, why he is so scared of "
           "you. Probably that is, because you are a friend of his boss.",
           BlackIvoryTower::lunatic()));
    if (_hadADoener)
    {
        Console::printLn(tr("You already know what to expect. Döner is great, Döner is tasty and for sure, Döner makes "
                            "you more beautiful."));
        Console::printLn(tr("If only you knew, where the urge to put onions on your head is coming from?"));
    }
    else
    {
        Console::printLn(
            tr("So this is a Döner. It is probably the best thing you have ever eaten. It is savory and "
               "tasty and the home made garlic sauce tastes like heaven. You quickly think about making "
               "something similar in your {}sand{}wich{} shop, but decide, that this market belongs to {}. "
               "You feel a strong urge to put onions on your head, and you are sure, that the onions will "
               "make you look more beautiful.",
               CC::fgYellow(),
               CC::fgGreen(),
               CC::ccReset(),
               Ressources::Game::mobi()));
        CGameManagement::getPlayerInstance()->addXp(99);
    }

    _hadADoener = true;
    CGameManagement::getPlayerInstance()->addHp(1);
}

bool CDoenerInteraction::interactionAvailable() const
{
    return CNpcInteraction::interactionAvailable();
}

nlohmann::json CDoenerInteraction::save() const
{
    auto json = CNpcInteraction::save();
    json[TagNames::BlackIvoryTower::hadADoener] = _hadADoener;
    return nlohmann::json();
}

void CDoenerInteraction::load(const nlohmann::json& json)
{
    CNpcInteraction::load(json);
    _hadADoener = json[TagNames::BlackIvoryTower::hadADoener];
}

void CDoenerInteraction::makeNav(CMenu& menu)
{
    _nav = menu.createAction({"Have a Döner", 'H'});
}

std::string CDoenerInteraction::translatorModuleName() const
{
    return BlackIvoryTower::moduleName();
}
