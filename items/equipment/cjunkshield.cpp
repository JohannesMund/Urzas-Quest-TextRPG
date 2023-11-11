#include "cjunkshield.h"
#include "cenemy.h"
#include "colorconsole.h"
#include "console.h"
#include "randomizer.h"

#include <algorithm>
#include <format>

CJunkShield::CJunkShield() : CShield()
{

    _levelCap = 4;
    _namesByLevel = {
        "wheathered wooden board", "wooden board", "robust wooden board", "strong", "looks like an actual shield"};
    _description = "A wooden board. It can protect you from... well, not much but it offers a little protection.";

    _type = CEquipment::EType::eShield;
    _quality = CEquipment::EQuality::eJunk;
}

std::string CJunkShield::name() const
{
    return CC::colorizeString(CEquipment::name(), CC::fgLightCyan(), CC::fgCyan());
}

void CJunkShield::battleEffect(CEnemy* enemy)
{
    if (_level < 1)
    {
        Console::printLn("You raise your shield to protect you, but it does not look trustworthy at all");
    }
    else
    {
        Console::printLn("You raise your shield to protect you.");
    }
}

void CJunkShield::battleBuff(CEnemy* enemy, bool& endRound)
{
    if (doesEquipmentEffectFire())
    {
        Console::printLn("Your shield protects you from the enemy attack");
        enemy->dealDamage(1);
        endRound = true;
    }
}
