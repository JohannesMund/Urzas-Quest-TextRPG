#include "cgamemanagement.h"
#include "clog.h"
#include "cmenu.h"
#include "console.h"
#include "ressources.h"
#include "translator/ctranslator.h"

#include <iostream>

using namespace std;

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

    CGameManagement::getGameSettingsInstance()->setCurrentLanguage(in.getName());
}

void printOptionsMenu()
{
    Console::cls(false);
    printTitle();

    CMenu menu;
    CMenu::ActionList startMenuActions;

    const auto languageAction = menu.createAction("Language options", 'l');
    menu.addMenuGroup({languageAction}, {CMenu::ret()});

    if (menu.execute() == languageAction)
    {
        printLanguageMenu();
    }
}

int main()
{
    Console::setEcho(false);

    while (true)
    {
        Console::cls(false);
        printTitle();

        CMenu menu;
        const auto newGameAction = menu.createAction("Start a new game", 's');
        const auto loadGameAction = menu.createAction("Load game", 'l');
        const auto optionsAction = menu.createAction("Options", 'O');
        const auto quitAction = menu.createAction("Quit game", 'q');

        if (CGameManagement::saveGameAvailable())
        {
            menu.addMenuGroup({newGameAction}, {loadGameAction});
        }
        else
        {
            menu.addMenuGroup({newGameAction});
        }
        menu.addMenuGroup({optionsAction}, {quitAction});
        auto in = menu.execute();

        if (in == newGameAction)
        {
            CGameManagement::getInstance()->startGame();
            break;
        }

        if (in == loadGameAction)
        {
            CGameManagement::getInstance()->loadGame();
            break;
        }

        if (in == optionsAction)
        {
            printOptionsMenu();
        }

        if (in == quitAction)
        {
            break;
        }
    }
    Console::setEcho(true);
}
