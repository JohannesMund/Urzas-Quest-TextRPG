#include "cbountyhunt.h"
#include "cbattle.h"
#include "cbountyenemy.h"
#include "cgamemanagement.h"
#include "console.h"

#include <format>

bool CBountyHunt::huntActive = false;

CBountyHunt::CBountyHunt(const std::string& name, const unsigned int reward) : CTask(), _name(name), _reward(reward)
{
    huntActive = true;
}

CBountyHunt::~CBountyHunt()
{
    huntActive = false;
    CTask::~CTask();
}

bool CBountyHunt::isHuntActive()
{
    return huntActive;
}

void CBountyHunt::execute()
{
    Console::printLn(std::format("Finally, you found you bounty! {} is there, counting his riches and doing evil "
                                 "things, he does not expect you. You draw your weapon and charge!",
                                 _name));

    CBountyEnemy bounty(_name);

    CBattle battle(&bounty);
    battle.fight();

    if (bounty.isDead())
    {
        Console::printLn("This is the end of the criminal master mind. The world us safe again. But, for how long?");
        CGameManagement::getPlayerInstance()->gainGold(_reward);
        Console::printLn("You grab your reward, and continue your adventure.");
    }
    else
    {
        Console::printLn("You failed miserably!");
        if (!CGameManagement::getPlayerInstance()->isDead())
        {
            Console::printLn("At least you survived. Bounty hunter does not seem to be the fitting job choice for you. "
                             "Maybe bus driver would be better. Are there busses here in this wordl?");
        }
    }

    Console::br();
    Console::confirmToContinue();

    _isFinished = true;
}

std::string CBountyHunt::name() const
{
    return _name;
}
