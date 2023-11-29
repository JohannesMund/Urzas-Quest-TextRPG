#include "claylasribbon.h"
#include "console.h"
#include "ressources.h"

#include <format>

CLaylasRibbon::CLaylasRibbon()
{
    _name = std::format("{}s {}", Ressources::Game::princessLayla(), Ressources::Game::laylasRibbon());
    _description = std::format("The ribbon of {}. She gave it to you as a lucky charm and to protect you. You will "
                               "honor this precious treasure forever",
                               Ressources::Game::princessLayla());
}

void CLaylasRibbon::battleEffect(CEnemy* enemy)
{
    Console::printLn(std::format("The power of {}s love protects you.", Ressources::Game::princessLayla()));
}

int CLaylasRibbon::shield(const unsigned int i)
{
    Console::printLn(std::format("{} protects you with the love of {}", _name, Ressources::Game::princessLayla()));
    return i - 1;
}
