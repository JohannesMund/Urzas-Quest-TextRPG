#include "csewertask.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorconsole.h"
#include "console.h"
#include "csewerdungeon.h"
#include "csewerdungeonmap.h"
#include "ctown.h"
#include "moduleressources.h"

#include <format>
#include <string>

CSewerTask::CSewerTask()
{
    _isAutoExecute = false;
}

void CSewerTask::execute()
{
    std::string townName;
    auto town = dynamic_cast<CTown*>(CGameManagement::getInstance()->currentRoom());
    if (town != nullptr)
    {
        townName = town->name();
    }

    Console::printLn(std::format(
        "{}, There is a job to be done. You will have to go down into the {}sewers{}, and find the missing children. "
        "The smell coming out of the sewer pipe, wich will act as you entry is disgusting!",
        townName,
        CC::fgYellow(),
        CC::ccReset()));

    Console::printLn("Do you think it is time to go down now?");
    Console::br();

    if (CMenu::executeYesNoMenu() == CMenu::no())
    {
        return;
    }

    executeDungeon();

    if (CGameManagement::getPlayerInstance()->isDead())
    {
        return;
    }
    Console::printLn(std::format(
        "You bring the children back to the surface and everybody is happy to see them again. You instantly start "
        "asking around for the secret chapel you found down there, but as soon as you ask, or use the word {0} "
        "people stop talking or evade the talk. Eventually, one of the towns elders warns you, to continue asking "
        "questions about {0} or talking about anything you have seen down there.",
        Ressources::Game::urza()));
    Console::printLn("Thankfullness is different.");
    _isFinished = true;
}

std::string CSewerTask::taskNav() const
{
    return SewerRessources::encounterName();
}

void CSewerTask::executeDungeon()
{
    CSewerDungeonMap map(12, 19);
    map.setStartingPosition({10, 7});
    map.init();

    CSewerDungeon dungeon;
    dungeon.setDungeonMap(&map);

    dungeon.addHealingWell(
        SewerRessources::getWellDescription(1), SewerRessources::getWellQuestion(1), SewerRessources::getWellEffect(1));
    dungeon.addHealingWell(
        SewerRessources::getWellDescription(2), SewerRessources::getWellQuestion(2), SewerRessources::getWellEffect(2));

    dungeon.addMapRoom(SewerRessources::getMapRoomDescription());

    dungeon.execute();
}
