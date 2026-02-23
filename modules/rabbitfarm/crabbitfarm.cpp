#include "crabbitfarm.h"
#include "colorize.h"
#include "console.h"
#include "rabbitfarm/moduleressources.h"

CRabbitFarm::CRabbitFarm() :
    CRoom(TagNames::RabbitFarm::rabbitFarm),
    _slasher(&_kat, &_rabbits),
    _rabbitHatch(&_kat, &_rabbits)
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

        auto slasherAction = _slasher.townModuleNav(menu);
        auto hatchAction = _rabbitHatch.townModuleNav(menu);

        menu.addMenuGroup({hatchAction}, {CMenu::exit()});
        menu.addMenuGroup({slasherAction});

        input = menu.execute();
        if (input == slasherAction)
        {
            _slasher.execute();
        }
        if (input == hatchAction)
        {
            _rabbitHatch.execute();
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
    nlohmann::json o;
    o["RabbitMap"] = _rabbits.save();
    o["KatNothingH"] = _kat.save();
    return o;
}

void CRabbitFarm::load(const nlohmann::json& json)
{
    _rabbits.load(json["RabbitMap"]);
    _kat.load(json["KatNothingH"]);
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
