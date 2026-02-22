#include "crabbitfarm.h"
#include "colorize.h"
#include "console.h"
#include "rabbitfarm/moduleressources.h"

CRabbitFarm::CRabbitFarm() : CRoom(TagNames::RabbitFarm::rabbitFarm), _slasher(&_kat), _rabbitHatch(&_kat)
{
    _showInFogOfWar = true;
}

void CRabbitFarm::execute()
{
    CRoom::execute();

    CMenuAction input;
    do
    {
        printHeader();
        CMenu menu(RabbitFarm::moduleName());

        auto npcAction = _kat.npcNav(menu);
        auto slasherAction = _slasher.townModuleNav(menu);
        auto hatchAction = _rabbitHatch.townModuleNav(menu);

        menu.addMenuGroup({npcAction});
        menu.addMenuGroup({slasherAction, hatchAction}, {CMenu::exit()});
        input = menu.execute();
        if (input == npcAction)
        {
            _kat.interact();
        }

        if (input == slasherAction)
        {
            _slasher.execute();
        }

    } while (input != CMenu::exit());
}

std::string CRabbitFarm::bgColor() const
{
    return CC::bgDarkGray();
}

std::string CRabbitFarm::fgColor() const
{
    return CC::fgLightYellow();
}

std::string CRabbitFarm::translatorModuleName() const
{
    return RabbitFarm::moduleName();
}

nlohmann::json CRabbitFarm::save() const
{
    return nlohmann::json();
}

void CRabbitFarm::load(const nlohmann::json&)
{
}

char CRabbitFarm::getMapSymbol() const
{
    return 94;
}

void CRabbitFarm::printHeader() const
{
    Console::cls();

    Console::printLn(RabbitFarm::rabbitHatchName(), Console::EAlignment::eCenter);
    Console::br();
}
