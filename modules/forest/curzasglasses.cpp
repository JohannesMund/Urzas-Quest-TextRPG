#include "curzasglasses.h"
#include "cenemy.h"
#include "colorconsole.h"
#include "console.h"
#include "randomizer.h"

#include <format>
#include <random>

CUrzasGlasses::CUrzasGlasses()
{

    _name = std::format("{}Ur{}za{}s'{} G{}la{}ss{}es{}",
                        CC::fgGreen(),
                        CC::fgLightGreen(),
                        CC::fgYellow(),
                        CC::fgLightYellow(),
                        CC::fgYellow(),
                        CC::fgLightGreen(),
                        CC::fgGreen(),
                        CC::ccReset());
    _description =
        "An old pair of glasses. Your sight does not change at all, when wearing them, but nevertheless, you realize 2 "
        "things:\n 1. The are magic as f***\n 2.You look incredibly stupid, when wearing them.";

    _isSellable = true;
    _value = 3000;
    _hasBattleBuff = true;
}

void CUrzasGlasses::battleBuff(CEnemy* enemy, bool& endRound)
{
    if (endRound)
    {
        return;
    }

    auto enemysChoice = enemy->peek();
    if (enemysChoice.has_value())
    {
        std::vector<CBattle::EWeapons> notSelected;

        auto addWeapon = [&notSelected, enemysChoice](CBattle::EWeapons weapon)
        {
            if (*enemysChoice != weapon)
            {
                notSelected.push_back(weapon);
            }
        };

        addWeapon(CBattle::EWeapons::eRock);
        addWeapon(CBattle::EWeapons::ePaper);
        addWeapon(CBattle::EWeapons::eScissors);

        if (enemy->hasExtendedWeaponChoice())
        {
            addWeapon(CBattle::EWeapons::eLizard);
            addWeapon(CBattle::EWeapons::eSpock);
        }

        std::shuffle(
            notSelected.begin(), notSelected.end(), std::default_random_engine(Randomizer::getRandomEngineSeed()));

        Console::printLn(std::format("The magic of {} tell you, that your enemy does not choose {}",
                                     _name,
                                     CBattle::weapon2String(notSelected.at(0))));
    }
}
