#include "cgiftinteraction.h"
#include "cdateinteraction.h"
#include "cgamemanagement.h"
#include "cnpc.h"
#include "console.h"
#include "randomizer.h"

CGiftInteraction::CGiftInteraction(CNpc* npc, CItem::ItemFilter itemFilter) :
    CNpcInteraction(npc, TagNames::NpcInteractions::gift),
    _itemFilter(itemFilter)
{
}
void CGiftInteraction::executeInteraction()
{
    CNpcInteraction::executeInteraction();
    auto item = CGameManagement::getInventoryInstance()->getFirstBasicItemByFilter(_itemFilter);
    if (!item.has_value())
    {
        Console::printLn(tr("Well, this is emberrassing. You search your bag for {}s, but apperently you have none.",
                            item.value()->name()));
        Console::printLn(tr("{} looks dissapointed.", _npc->name()));
        return;
    }
    CGameManagement::getInventoryInstance()->removeItem(item.value());

    auto sympathy = 10 + Randomizer::getRandom(40);
    if (sympathy > 45)
    {
        Console::printLn(
            tr("{}s Eyes are gleaming, when {} sees you {}. This must be the most beautiful apple she has ever seen",
               _npc->name(),
               _npc->heShe(),
               item.value()->name()));
    }
    else if (sympathy > 25)
    {
        Console::printLn(
            tr("{0} seems to like your {1}. You think, this is a beautiful {1}.", _npc->name(), item.value()->name()));
    }
    else
    {
        Console::printLn(tr(
            "{0} thanks you politely, and puts your {1} to {2} other {1}s. It is the gesture that counts, you guess.",
            _npc->name(),
            item.value()->name(),
            _npc->hisHer()));
    }

    _npc->addSympathy(sympathy);
    Console::br();
}

bool CGiftInteraction::interactionAvailable() const
{
    return CNpcInteraction::interactionAvailable() && CGameManagement::getInventoryInstance()->hasItem(_itemFilter);
}

void CGiftInteraction::makeNav(CMenu& menu)
{
    _nav = menu.createAction({"Special Gift", 'G'});
}
