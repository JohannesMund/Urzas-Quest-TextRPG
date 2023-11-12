#include "chealingwell.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"

CHealingWell::CHealingWell()
{
}

void CHealingWell::execute()
{
    CDungeonRoom::execute();

    Console::br();
    Console::printLn(_question);
    Console::br();
    if (CMenu::yes(CMenu::executeYesNoMenu()))
    {
        Console::printLn(_effect);
        CGameManagement::getPlayerInstance()->addHp(9999);
        Console::br();
        Console::confirmToContinue();
    }
}

std::string CHealingWell::mapSymbol() const
{
    return "w";
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