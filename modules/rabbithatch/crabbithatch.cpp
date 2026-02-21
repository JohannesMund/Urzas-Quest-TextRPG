#include "crabbithatch.h"
#include "colorize.h"
#include "console.h"
#include "rabbithatch/moduleressources.h"

CRabbitHatch::CRabbitHatch() : CRoom(TagNames::RabbitHatch::rabbitHatch)
{
    _showInFogOfWar = true;
}

void CRabbitHatch::execute()
{
    CRoom::execute();

    CMenuAction input;
    do
    {
        printHeader();
        CMenu menu(RabbitHatch::moduleName());
        auto npcAction = _kat.npcNav(menu);
        menu.addMenuGroup({npcAction}, {CMenu::exit()});
        input = menu.execute();
        if (input == npcAction)
        {
            _kat.interact();
        }
    } while (input != CMenu::exit());
}

std::string CRabbitHatch::bgColor() const
{
    return CC::bgDarkGray();
}

std::string CRabbitHatch::fgColor() const
{
    return CC::fgLightYellow();
}

std::string CRabbitHatch::translatorModuleName() const
{
    return RabbitHatch::moduleName();
}

nlohmann::json CRabbitHatch::save() const
{
    return nlohmann::json();
}

void CRabbitHatch::load(const nlohmann::json&)
{
}

char CRabbitHatch::getMapSymbol() const
{
    return 94;
}

void CRabbitHatch::printHeader() const
{
    Console::cls();

    Console::printLn(RabbitHatch::rabbitHatchName(), Console::EAlignment::eCenter);
    Console::br();
}
