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

    Console::printLn("[S]tart a new game", Console::EAlignment::eCenter);
    Console::printLn("[Q]uit game", Console::EAlignment::eCenter);

    char in = Console::getAcceptableInput("sq");
    if (in == 's')
    {
        CGameManagement::getInstance();
    }

    cout << endl;
    Console::setEcho(true);
}
