#include "claylasribbon.h"
#include "console.h"
#include "ressources.h"

#include <format>

CLaylasRibbon::CLaylasRibbon() : CItem(TagNames::Item::Story::laylasRibbon)
{
    _name = std::format("{}s {}", Ressources::Game::princessLeila(), Ressources::Game::leilasRibbon());
    _description = coreTr("The ribbon of {}. She gave it to you as a lucky charm and to protect you. You will "
                          "honor this precious treasure forever",
                          Ressources::Game::princessLeila());
}

void CLaylasRibbon::battleEffect(CEnemy*)
{
    Console::printLn(coreTr("The power of {}s love protects you.", Ressources::Game::princessLeila()));
}

int CLaylasRibbon::shield(const unsigned int i)
{
    Console::printLn(coreTr("{} protects you with the love of {}", _name, Ressources::Game::princessLeila()));
    return i - 1;
}

std::string CLaylasRibbon::translatorModuleName() const
{
    return std::string();
}
