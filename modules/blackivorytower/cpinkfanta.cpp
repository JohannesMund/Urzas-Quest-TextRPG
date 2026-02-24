#include "cpinkfanta.h"
#include "blackivorytower/moduleressources.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "randomizer.h"

CPinkFanta::CPinkFanta() : CItem(TagNames::BlackIvoryTower::pinkFanta)
{
    _name = BlackIvoryTower::pinkFanta();
    _description = tr("A mystrious, sparkling {}pink{} brew, the label reads: {}\"Pour a dragon down your throat\"{}",
                      CC::fgMagenta(),
                      CC::ccReset(),
                      CC::fgLightMagenta(),
                      CC::ccReset());

    _isBuyable = true;
    _isSellable = true;
    _value = 250;
    _isUsableFromBattle = true;
    _isUsableFromInventory = true;
    _isConsumable = true;
}

CItem::ItemFilter CPinkFanta::pinkFantaFilter()
{
    return [](const CItem* item) { return dynamic_cast<const CPinkFanta*>(item) != nullptr; };
}

void CPinkFanta::useFromInventory()
{
    Console::printLn("You open the bottle, and swallow it in one draw. Healing potions are disgusting!");
    use();
}

void CPinkFanta::useFromBattle(CEnemy*)
{
    Console::printLn("It is in the middle of a hot fight, but you need healing.");
    use();
}

std::string CPinkFanta::translatorModuleName() const
{
    return std::string(BlackIvoryTower::moduleName());
}

void CPinkFanta::use()
{
    Console::printLn(tr("It is {0}pink{1} and {2}sparkling{1} and {0}pink{1}. You can feel the {3}Dragon{1}",
                        CC::fgMagenta(),
                        CC::ccReset(),
                        CC::fgCyan(),
                        CC::fgRed()));
    CGameManagement::getPlayerInstance()->addHp(Randomizer::getRandom(6) + 2);
}
