#include "ccompanion.h"
#include "cenemy.h"
#include "console.h"
#include "randomizer.h"

#include <format>
#include <string>

std::string CCompanion::description() const
{
    return _description;
}

unsigned int CCompanion::level() const
{
    return _level;
}

bool CCompanion::hasCompanion() const
{
    return _level > 0;
}

void CCompanion::evolve()
{
    if (_level >= Ressources::Companion::companionLevelCap)
    {
        return;
    }

    auto oldName = name();
    _level++;
    auto newName = name();

    if (_level == 1)
    {
        Console::printLn(std::format(
            "Finally, you found a friend! Your first friend ever! you pet your little {} and continue your journey.",
            newName));
    }
    else
    {
        Console::printLn(std::format("Your {} evolved into a {}", oldName, newName));
    }
}

bool CCompanion::fireDefaultAction() const
{
    if (_level == 0)
    {
        return false;
    }
    return Randomizer::getRandom(Ressources::Companion::companionLevelCap + 2 - _level) == 0;
}
