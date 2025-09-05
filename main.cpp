#include "cgamemanagement.h"
#include "console.h"
#include "ressources.h"

#include <iostream>

using namespace std;

int main()
{
    Console::setEcho(false);
    Console::cls(false);

    Console::hr();
    Console::printLn("T H E   Q U E S T   O F   U R Z A", Console::EAlignment::eCenter);
    Console::printLn("~or~", Console::EAlignment::eCenter);
    Console::printLn(Ressources::Game::whoTheFuckIsUrza(), Console::EAlignment::eCenter);
    Console::hr();

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
