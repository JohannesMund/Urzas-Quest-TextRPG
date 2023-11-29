#include "chealingwell.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"

CHealingWell::CHealingWell() : CDungeonRoom()
{
}

void CHealingWell::execute()
{
    CDungeonRoom::execute();

    Console::br();
    Console::printLn(_question);
    Console::br();
    if (CMenu::executeYesNoMenu() == CMenu::yes())
    {
        Console::printLn(_effect);
        CGameManagement::getPlayerInstance()->fullHeal();
        Console::br();
        Console::confirmToContinue();
    }
}

void CHealingWell::setQuestion(const std::string_view& question)
{
    _question = question;
}

void CHealingWell::setEffect(const std::string_view& effect)
{
    _effect = effect;
}

bool CHealingWell::isSpecialRoom() const
{
    return true;
}

char CHealingWell::getMapSymbol() const
{
    return 'w';
}
