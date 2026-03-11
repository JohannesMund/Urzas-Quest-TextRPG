#include "cgeminteraction.h"

#include "cgamemanagement.h"
#include "cmenu.h"
#include "cnpc.h"
#include "console.h"
#include "randomizer.h"
#include "wonderlamp/items/cgem.h"
#include "wonderlamp/moduleressources.h"

CGemInteraction::CGemInteraction(CNpc* npc) : CNpcInteraction(npc, TagNames::WonderLamp::gemInteractiom)
{
}

void CGemInteraction::executeInteraction()
{
    auto gem = CGameManagement::getInventoryInstance()->getFirstItemByFilter<CGem>(CGem::gemFilter());
    if (!gem.has_value())
    {
        Console::printLn(tr("Turns out, you dont have a gem."));
        return;
    }

    CGameManagement::getInventoryInstance()->removeItem(gem.value());

    auto sympathy = 10 + Randomizer::getRandom(40);
    if (sympathy > 45)
    {
        Console::printLn(tr("Djinns love gems, more than everything else. {0} eyes are shining, when {1} sees the "
                            "valuable {2}. {1} takes the gem, and puts it into {3} treasury.",
                            _npc->name(),
                            _npc->heShe(),
                            gem.value()->name(),
                            _npc->hisHer()));
    }
    else if (sympathy > 25)
    {
        Console::printLn(tr("{0} seems to like your {1}. {2} appreciates your gift.",
                            _npc->name(),
                            gem.value()->name(),
                            _npc->heShe()));
    }
    else
    {
        Console::printLn(tr("{0} thanks you politely, and puts your {1} into {2} treasury. It is small, and not very "
                            "clear, but it is the gesture that counts, you guess.",
                            _npc->name(),
                            gem.value()->name(),
                            _npc->hisHer()));
    }

    _npc->addSympathy(sympathy);
    Console::br();
}

bool CGemInteraction::interactionAvailable() const
{
    return CGameManagement::getInventoryInstance()->hasItem(CGem::gemFilter());
}

void CGemInteraction::makeNav(CMenu& menu)
{
    _nav = menu.createAction({"Gift gem", 'G'});
}

std::string CGemInteraction::translatorModuleName() const
{
    return WonderLamp::moduleName();
}
