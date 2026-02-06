#include "clunatic.h"
#include "colorize.h"
#include "moduleressources.h"
#include "randomizer.h"

#include <format>

CLunatic::CLunatic() : CMobEnemy()
{
    switch (Randomizer::getRandom(3))
    {
    case 0:
    default:
        _name = std::format("{} {}Warrior{}", BlackIvoryTower::lunatic(), CC::fgDarkGray(), CC::ccReset());
        _weapon = std::format("{} {}Sword{}", BlackIvoryTower::lunatic(), CC::fgDarkGray(), CC::ccReset());
        _type = ELunaticType::eWarrior;
        break;
    case 1:
        _name = std::format("{} {}Defender{}", BlackIvoryTower::lunatic(), CC::fgLightGray(), CC::ccReset());
        _weapon = std::format("{} {}Axe{}", BlackIvoryTower::lunatic(), CC::fgLightGray(), CC::ccReset());
        _type = ELunaticType::eDefender;
        break;
    case 2:
        _name = std::format("{} {}Mage{}", BlackIvoryTower::lunatic(), CC::fgLightMagenta(), CC::ccReset());
        _weapon = std::format("{} {}Wand{}", BlackIvoryTower::lunatic(), CC::fgLightMagenta(), CC::ccReset());
        _specialAttackChance = std::max(0U, _specialAttackChance - 2U);
        _type = ELunaticType::eMage;
        break;
    }
}

unsigned int CLunatic::damage() const
{
    if (_type == ELunaticType::eWarrior)
    {
        return CMobEnemy::damage() + 1;
    }

    return CMobEnemy::damage();
}

int CLunatic::shieldingAction(const int damage) const
{
    if (_type == ELunaticType::eDefender)
    {
        return damage - 1;
    }
    return damage;
}
