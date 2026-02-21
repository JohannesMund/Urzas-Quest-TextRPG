#include "crabbithatchapple.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "rabbithatch/moduleressources.h"
#include "randomizer.h"

CRabbithatchApple::CRabbithatchApple() : CItem(TagNames::RabbitHatch::apple)
{
    _name = tr("{}A{}pple{}", CC::fgLightYellow(), CC::fgRed(), CC::ccReset());
    _description = tr("A beautiful {}A{}pple{} just like the ones, {} described to you.",
                      CC::fgLightYellow(),
                      CC::fgRed(),
                      CC::ccReset(),
                      RabbitHatch::katNothingH());

    _isConsumable = true;
    _isUsableFromInventory = true;
    _isUsableFromBattle = true;
    _isSellable = true;
}

void CRabbithatchApple::useFromInventory()
{
    Console::printLn(tr("You are a little hungry, so let's eat"));
    use();
}

void CRabbithatchApple::useFromBattle(CEnemy*)
{
    Console::printLn(tr("You should not have time for lunch in the middle of a fight, but maybe this helps."));
    use();
}

CItem::ItemFilter CRabbithatchApple::aopleFilter()
{
    return [](const CItem* item) { return dynamic_cast<const CRabbithatchApple*>(item) != nullptr; };
}

std::string CRabbithatchApple::translatorModuleName() const
{
    return std::string(RabbitHatch::moduleName());
}

void CRabbithatchApple::use()
{
    Console::printLn(tr("This is delicious. Sweet, refreshing, revitalizing"));
    CGameManagement::getPlayerInstance()->addHp(Randomizer::getRandom(3) + 1);
}