#include "cgamemanagement.h"
#include "clog.h"
#include "cmenu.h"
#include "console.h"
#include "ressources.h"
#include "translator/ctranslator.h"

#include <iostream>

using namespace std;

std::string tr(const std::string_view& s)
{
    return CTranslator::getInstance()->tr("core", "startMenu", s);
}

void printTitle()
{
    Console::hr();
    Console::printLn(" _    _                      ____                  _   ", Console::EAlignment::eCenter);
    Console::printLn("| |  | |                    / __ \\                | |  ", Console::EAlignment::eCenter);
    Console::printLn("| |  | |_ __ ______ _ ___  | |  | |_   _  ___  ___| |_ ", Console::EAlignment::eCenter);
    Console::printLn("| |  | | '__|_  / _` / __| | |  | | | | |/ _ \\/ __| __|", Console::EAlignment::eCenter);
    Console::printLn("| |__| | |   / / (_| \\__ \\ | |__| | |_| |  __/\\__ \\ |_ ", Console::EAlignment::eCenter);
    Console::printLn(" \\____/|_|  /___\\__,_|___/  \\___\\_\\__,_|\\___||___/\\___|", Console::EAlignment::eCenter);
    Console::printLn("~or~", Console::EAlignment::eCenter);
    Console::printLn(Ressources::Game::whoTheFuckIsUrza(), Console::EAlignment::eCenter);
    Console::hr();
}

void printLanguageMenu()
{
    Console::cls(false);
    printTitle();

    CMenu menu;
    CMenu::ActionList languageActions;

    for (const auto s : CGameSettings::supportedLanguages())
    {
        languageActions.push_back(menu.createAction(s));
    }

    menu.addMenuGroup(languageActions, {CMenu::ret()});

    auto in = menu.execute();

    if (in == CMenu::ret())
    {
        return;
    }

    CGameManagement::getGameSettingsInstance()->setCurrentLanguage(in.name);
}

void printOptionsMenu()
{
    Console::cls(false);
    printTitle();

    CMenu menu;
    CMenu::ActionList startMenuActions;

    menu.addMenuGroup({menu.createAction(tr("Language options"), 'l')}, {CMenu::ret()});

    auto in = menu.execute();

    if (in.key == 'l')
    {
        printLanguageMenu();
    }
}

CMenu::Action printTitleMenu()
{
    printTitle();
    CMenu menu;
    if (CGameManagement::saveGameAvailable())
    {
        menu.addMenuGroup({menu.createAction(tr("Start a new game"), 's')}, {menu.createAction(tr("Load game"), 'l')});
    }
    else
    {
        menu.addMenuGroup({menu.createAction(tr("Start a new game"), 's')});
    }
    menu.addMenuGroup({menu.createAction(tr("Options"), 'O')}, {menu.createAction(tr("Quit game"), 'q')});
    return menu.execute();
}

int main()
{
    Console::setEcho(false);

    while (true)
    {
        Console::cls(false);
        auto in = printTitleMenu();
        cout << endl;

        if (in.key == 's')
        {
            CGameManagement::getInstance()->startGame();
            break;
        }

        if (in.key == 'l')
        {
            CGameManagement::getInstance()->loadGame();
            break;
        }

        if (in.key == 'o')
        {
            printOptionsMenu();
        }

        if (in.key == 'q')
        {
            break;
        }
    }
    Console::setEcho(true);
}
