#include "capple.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "rabbitfarm/moduleressources.h"
#include "randomizer.h"

CApple::CApple() : CItem(TagNames::RabbitFarm::apple)
{
    _name = RabbitFarm::apple();
    _description = tr("A beautiful {}A{}pple{} just like the ones, {} described to you.",
                      CC::fgLightYellow(),
                      CC::fgRed(),
                      CC::ccReset(),
                      RabbitFarm::katNothingH());

    _isConsumable = true;
    _isUsableFromInventory = true;
    _isUsableFromBattle = true;
    _isSellable = true;
}

void CApple::useFromInventory()
{
    Console::printLn(tr("You are a little hungry, so let's eat"));
    use();
}

void CApple::useFromBattle(CEnemy*)
{
    Console::printLn(tr("You should not have time for lunch in the middle of a fight, but maybe this helps."));
    use();
}

CItem::ItemFilter CApple::aopleFilter()
{
    return [](const CItem* item) { return dynamic_cast<const CApple*>(item) != nullptr; };
}

std::string CApple::translatorModuleName() const
{
    return std::string(RabbitFarm::moduleName());
}

void CApple::use()
{
    Console::printLn(tr("This is delicious. Sweet, refreshing, revitalizing"));
    CGameManagement::getPlayerInstance()->addHp(Randomizer::getRandom(3) + 1);
}