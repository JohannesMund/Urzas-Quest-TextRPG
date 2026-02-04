#include "cgamemanagement.h"
#include "clog.h"
#include "console.h"
#include "ressources.h"

#include <iostream>

using namespace std;

int main()
{
    Console::setEcho(false);
    Console::cls(false);

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

    CLog::info() << "Bratwurst" << std::endl << std::flush;

    std::string acceptableChars;
    Console::printLn("[S]tart a new game", Console::EAlignment::eCenter);
    acceptableChars += 's';

    if (CGameManagement::saveGameAvailable())
    {
        Console::printLn("[L]oad game", Console::EAlignment::eCenter);
        acceptableChars += 'l';
    }

    Console::printLn("[Q]uit game", Console::EAlignment::eCenter);
    acceptableChars += 'q';

    unsigned char in = Console::getAcceptableInput(acceptableChars);
    if (in == 's')
    {
        CGameManagement::getInstance()->startGame();
    }

    if (in == 'l')
    {
        CGameManagement::getInstance()->loadGame();
    }

    cout << endl;
    Console::setEcho(true);
}
