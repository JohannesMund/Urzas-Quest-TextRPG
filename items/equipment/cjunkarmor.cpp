#include "cjunkarmor.h"
#include "cenemy.h"
#include "colorconsole.h"
#include "console.h"
#include "randomizer.h"

#include <format>
CJunkArmor::CJunkArmor() : CArmor()
{
    _levelCap = 4;
    _namesByLevel = {"Ripped T-Shirt", "White T-Shirt", "Fashionable T-Shirt", "Sweater", "Hoodie"};
    _description = "Looks like mere clothing, but should offer a little protection.";

    _type = CEquipment::EType::eArmor;
    _quality = CEquipment::EQuality::eJunk;
}

std::string CJunkArmor::name() const
{
    return CC::colorizeString(CEquipment::name(), CC::fgLightGray(), CC::fgLightGray());
}

void CJunkArmor::battleEffect(CEnemy* enemy)
{
    Console::printLn(std::format("You feel confident, that your armor will protect you from the furious attacks of {}",
                                 enemy->name()));
}

int CJunkArmor::shield(const unsigned int i)
{
    int shieldAmount = Randomizer::getRandom(_level + 1);
    if (shieldAmount == 0)
    {
        return i;
    }

    if (Randomizer::getRandom(100) <= _level * 10)
    {
        Console::printLn(std::format("Your armor absorbs {} damage", shieldAmount));
        return std::max(i - shieldAmount, 0U);
    }

    return i;
}
