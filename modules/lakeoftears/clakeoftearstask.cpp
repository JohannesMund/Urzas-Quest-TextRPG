#include "clakeoftearstask.h"
#include "cbattle.h"
#include "cgamemanagement.h"
#include "clakeoftearsbosstask.h"
#include "cmobenemy.h"
#include "colorize.h"
#include "console.h"
#include "itemfactory.h"
#include "randomizer.h"

#include <format>
#include <string>

CLakeOfTearsTask::CLakeOfTearsTask(const unsigned int steps) : CTask(), _steps(steps)
{
}

void CLakeOfTearsTask::execute()
{

    Console::printLn("You follow the stream upward, und test the water from time to time. the longer you follow the "
                     "river, the saltier the water becomes.");
    Console::br();
    auto rnd = Randomizer::getRandom(10);

    switch (rnd)
    {
    case 0:
        Console::printLn("While testing the water, you find something hidden under a lily pad.");
        CGameManagement::getInventoryInstance()->addItem(ItemFactory::makeShopItem());
        break;
    case 1:
    case 2:
        Console::printLn("Some poor guy lost his purse here. Probably the disgusting water let him lower his guards");
        CGameManagement::getPlayerInstance()->addGold(Randomizer::getRandom(100) * 2 + 123);
        break;
    case 3:
    case 4:
    case 5:
        Console::printLn("There is something in the bushes");
        CGameManagement::getInventoryInstance()->addItem(ItemFactory::makeItem(ItemFactory::EItemType::eJunkItem));
        break;
    case 6:
        battle(EEnemy::eFrog);
        break;
    case 7:
        battle(EEnemy::eHornet);
        break;
    case 8:
        battle(EEnemy::eSnail);
        break;
    case 9:
        battle(EEnemy::eSnake);
        break;
    }

    if (CGameManagement::getPlayerInstance()->isDead())
    {
        return;
    }

    Console::confirmToContinue();

    if (_steps + Randomizer::getRandom(5) > 9)
    {
        CGameManagement::getInstance()->placeTaskOnField(new CLakeOfTearsBossTask());
    }
    else
    {
        CGameManagement::getInstance()->placeTaskOnField(new CLakeOfTearsTask(_steps + 1));
    }

    _isFinished = true;
}

void CLakeOfTearsTask::battle(const EEnemy enemyType)
{

    Console::printLn("Suddenly, you are attacked!");
    Console::confirmToContinue();

    CMobEnemy enemy;

    switch (enemyType)
    {
    case EEnemy::eFrog:
        enemy.setName(std::format("{}Gigantic {}Frog{}", CC::fgLightGreen(), CC::fgGreen(), CC::ccReset()));
        enemy.setWeapon(std::format("{}glibbery {}tongue{}", CC::fgLightRed(), CC::fgRed(), CC::ccReset()));
        break;
    case EEnemy::eHornet:
        enemy.setName(std::format("{0}H{1}o{0}r{1}n{0}e{1}t{2}", CC::fgYellow(), CC::fgDarkGray(), CC::ccReset()));
        enemy.setWeapon(std::format("{}stingy {}sting{}", CC::fgYellow(), CC::fgDarkGray(), CC::ccReset()));
        break;
    case EEnemy::eSnail:
        enemy.setName(std::format("{}Slimy {}Snail{}", CC::fgLightCyan(), CC::fgLightGreen(), CC::ccReset()));
        enemy.setWeapon(std::format("{0}so {1}mich {0}Slime{2}", CC::fgLightCyan(), CC::fgLightGreen(), CC::ccReset()));
        break;
    case EEnemy::eSnake:
        enemy.setName(std::format("{}Poisonous {}Snake{}", CC::fgLightGreen(), CC::fgLightYellow(), CC::ccReset()));
        enemy.setWeapon(std::format(
            "{}Teeth {}and {}tongue{}", CC::fgLightYellow(), CC::ccReset(), CC::fgLightRed(), CC::ccReset()));
        break;
    }

    CBattle battle(&enemy);
    battle.fight();
}
