#include "console.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "globals.h"
#include "ressources.h"

#include <algorithm>
#include <format>
#include <iostream>
#include <string>

#ifdef _USE_WINDOWS
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#endif

using namespace std;
void Console::confirmToContinue()
{
    cout << "[Press [c] to Continue]";
    getAcceptableInput("c");
    cout << endl;
}

void Console::cls(const bool bHud)
{
#ifdef _USE_WINDOWS
    system("cls");
#else
    system("clear");
#endif
    if (bHud)
    {
        CGameManagement::getInstance()->printHUD();
    }
}

unsigned char Console::getAcceptableInput(string_view acceptableChars)
{
    bool found = false;
    unsigned char input;
#ifdef _USE_WINDOWS
    while (!found)
    {
        input = _getch();
        if (acceptableChars.find(input) != string::npos)
        {
            found = true;
        }
    }
#else
    system("stty raw");
    while (!found)
    {
        input = getchar();

        if (acceptableChars.find(input) != string::npos)
        {
            found = true;
        }
    }
    system("stty cooked");
#endif
    return input;
}

void Console::br()
{
    cout << endl;
}

void Console::hr()
{
    for (unsigned int i = 0; i < Ressources::Settings::consoleWidth; i++)
    {
        cout << "=";
    }

    cout << endl;
}

void Console::setEcho(const bool on)
{

#ifdef _USE_WINDOWS
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    if (on)
    {
        SetConsoleMode(hStdin, mode | ENABLE_ECHO_INPUT);
    }
    else
    {
        SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
    }
#else
    struct termios term;
    tcgetattr(fileno(stdin), &term);

    if (on)
    {
        term.c_lflag |= ECHO;
    }
    else
    {
        term.c_lflag &= ~ECHO;
    }

    tcsetattr(fileno(stdin), 0, &term);
#endif
}

void Console::printLn(const std::string_view& text, const EAlignment align, const bool bReset)
{

    std::string s(text);

    if (CC::colorizedSize(s) > Ressources::Settings::consoleWidth)
    {
        size_t written = 0;
        while (written < s.size())
        {
            auto substring = CC::colorizedSubString(s, written, Ressources::Settings::consoleWidth);

            if ((written + substring.size()) >= s.size())
            {
                printLn(substring, align);
                return;
            }

            auto it = substring.find_last_of(" ");

            if (it == std::string::npos)
            {
                printLn(substring, align);
                written += substring.size();
            }
            else
            {
                auto subsubstring = substring.substr(0, ++it);
                printLn(subsubstring, align, false);
                written += subsubstring.size();
            }
        }
    }
    else
    {
        if (align == EAlignment::eCenter)
        {
            bool toggle = false;
            while (CC::colorizedSize(s) < Ressources::Settings::consoleWidth)
            {
                s.insert(toggle ? 0 : s.size(), 1, ' ');
                toggle = !toggle;
            }
        }
        else if (align == EAlignment::eRight)
        {
            while (CC::colorizedSize(s) < Ressources::Settings::consoleWidth)
            {
                s.insert(0, 1, ' ');
            }
        }
        cout << s;
        if (bReset)
        {
            cout << CC::ccReset();
        }
        cout << endl;
    }
}

void Console::printErr(const std::string_view& text)
{
    printLn(std::format("Error: {}{}{}", CC::fgRed(), text, CC::ccReset()));
}

std::optional<int> Console::getNumberInputWithEcho(const int min, const int max)
{

    cout << std::format("[Enter number between {} and {} (or 'x' to cancel)] ", min, max);

    while (true)
    {
        setEcho(true);
        std::string input;
        cin >> input;
        setEcho(false);

        if (!input.empty() && std::all_of(input.begin(), input.end(), ::isdigit))
        {
            int dIn = std::stoi(input);

            if (dIn >= min && dIn <= max)
            {
                return dIn;
            }
        }

        if (input.find('x') != std::string::npos)
        {
            return {};
        }
    }
}

void Console::printLnWithSpacer(const std::string& text1, const std::string& text2)
{
    if (CC::colorizedSize(text1) + CC::colorizedSize(text2) > Ressources::Settings::consoleWidth)
    {
        printLn(text1);
        printLn(text2, EAlignment::eRight);
        return;
    }

    std::string out(text1);
    while (CC::colorizedSize(out) + CC::colorizedSize(text2) < Ressources::Settings::consoleWidth)
    {
        out.append(" ");
    }
    out.append(text2);
    printLn(out);
}
