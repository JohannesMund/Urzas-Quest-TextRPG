#include "cappleinteraction.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "cnpc.h"
#include "console.h"
#include "rabbitfarm/encounters/cappletree.h"
#include "rabbitfarm/items/capple.h"
#include "rabbitfarm/moduleressources.h"
#include "randomizer.h"

CAppleInteraction::CAppleInteraction(CNpc* npc) : CNpcInteraction(npc, TagNames::RabbitFarm::appleInteraction)
{
    CGameManagement::getInstance()->registerEncounter(new CAppleTree(_npc));
}

void CAppleInteraction::executeInteraction()
{
    auto apple = CGameManagement::getInventoryInstance()->getFirstItemByFilter<CApple>(CApple::appleFilter());
    if (!apple.has_value())
    {
        Console::printLn(tr("Well, this is emberrassing. You search your bag for {}s, but apperently you have none.",
                            RabbitFarm::apple()));
        Console::printLn(tr("{} looks dissapointed.", RabbitFarm::katNottingH()));
        return;
    }
    CGameManagement::getInventoryInstance()->removeItem(apple.value());

    auto sympathy = 10 + Randomizer::getRandom(40);
    if (sympathy > 45)
    {
        Console::printLn(
            tr("{}s Eyes are gleaming, when she sees you {}. This must be the most beautiful apple she has ever seen",
               RabbitFarm::katNottingH(),
               RabbitFarm::apple()));
    }
    else if (sympathy > 25)
    {
        Console::printLn(tr("{0} seems to like your {1}. You think, this is a beautiful {1}.",
                            RabbitFarm::katNottingH(),
                            RabbitFarm::apple()));
    }
    else
    {
        Console::printLn(tr(
            "{0} thanks you politely, and puts your {1} to her other {1}s. It is the gesture that counts, you guess.",
            RabbitFarm::katNottingH(),
            RabbitFarm::apple()));
    }

    _npc->addSympathy(sympathy);
    Console::br();
}

bool CAppleInteraction::interactionAvailable() const
{
    return CGameManagement::getInventoryInstance()->hasItem(CApple::appleFilter());
}

void CAppleInteraction::makeNav(CMenu& menu)
{
    _nav = menu.createAction({"Give her an Apple", 'G'});
}

std::string CAppleInteraction::translatorModuleName() const
{
    return std::string(TagNames::RabbitFarm::appleInteraction);
}
