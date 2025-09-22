#include "cphoenixfeather.h"
#include "cgamemanagement.h"
#include "console.h"
#include "randomizer.h"

#include <format>

CPhoenixFeather::CPhoenixFeather() : CItem(TagNames::Item::phoenixFeather)
{
    _name = std::format("{}Ph{}oe{}ni{}x f{}ea{}th{}er{}",
                        CC::fgRed(),
                        CC::fgLightRed(),
                        CC::fgYellow(),
                        CC::fgLightYellow(),
                        CC::fgYellow(),
                        CC::fgLightRed(),
                        CC::fgRed(),
                        CC::ccReset());
    _description = "A huge feather glowing magically in red, orange and yellow. It looks a "
                   "little bit as if it is burning.";

    _value = 5000;
    _hasDeathEffect = true;
    _isConsumable = true;
    _isSellable = true;
}

void CPhoenixFeather::deathEffect()
{
    Console::printLn(std::format("An orange glow comes out of your pocket, the {} rises into the air, and lands on "
                                 "your head. it feels warm and refreshing.",
                                 _name));
    Console::printLn("Looks as if you ar lucky and survived this time.");
    while (CGameManagement::getPlayerInstance()->isDead())
    {
        CGameManagement::getPlayerInstance()->addHp(Randomizer::getRandom(4) + 2);
    }
}
