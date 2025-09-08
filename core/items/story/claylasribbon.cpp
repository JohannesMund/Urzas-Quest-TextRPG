#include "claylasribbon.h"
#include "console.h"
#include "ressources.h"

#include <format>

CLaylasRibbon::CLaylasRibbon() : CItem("CLaylasRibbon")
{
    _name = std::format("{}s {}", Ressources::Game::princessLeila(), Ressources::Game::leilasRibbon());
    _description = std::format("The ribbon of {}. She gave it to you as a lucky charm and to protect you. You will "
                               "honor this precious treasure forever",
                               Ressources::Game::princessLeila());
}

void CLaylasRibbon::battleEffect(CEnemy*)
{
    Console::printLn(std::format("The power of {}s love protects you.", Ressources::Game::princessLeila()));
}

int CLaylasRibbon::shield(const unsigned int i)
{
    Console::printLn(std::format("{} protects you with the love of {}", _name, Ressources::Game::princessLeila()));
    return i - 1;
}
