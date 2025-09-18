#include "cbattle.h"
#include "cenemy.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "cmobenemy.h"
#include "colorize.h"
#include "console.h"
#include "exceptions.h"
#include "randomizer.h"

#include <format>

CBattle::CBattle() : CBattle(new CMobEnemy)
{
}

CBattle::CBattle(CEnemy* enemy)
{
    _enemy = enemy;
}

void CBattle::fight()
{
    Console::printLn(std::format(
        "You encounter the enemy {}, who attacks you with his weapon {}!", _enemy->name(), _enemy->weapon()));
    Console::hr();

    CMenu menu;
    menu.addMenuGroup({menu.createAction("Fight"), menu.createAction("Run")});

    auto input = menu.execute();
    if (input.key == 'r')
    {
        Console::printLn(std::format("You are too scared of {}, so you decide to run away.", _enemy->name()));

        auto result = Randomizer::getRandom(10);

        if (result < 3)
        {
            Console::printLn(
                std::format("You are much faster than {}, so it was easy and you escape.", _enemy->name()));
            return;
        }
        else if (result < 6)
        {
            Console::printLn(
                std::format("This {} is pretty fast, you manage to escape, but you got hit.", _enemy->name()));
            CGameManagement::getPlayerInstance()->dealDamage(1, true);
            return;
        }
        else
        {
            Console::printLn(std::format(
                "This is bad! {} is really fast, and gets you, there is no way to avoid this fight.", _enemy->name()));
        }
        Console::confirmToContinue();
    }

    Console::cls();

    preBattle();
    battleLoop();
    postBattle();

    if (_enemy->isDead())
    {
        Console::printLn("You are victorious!");
        _enemy->spoilsOfWar();
        CGameManagement::getProgressionInstance()->increaseBodyCount();
    }
}

bool CBattle::isBattleOver() const
{
    if (_enemy == nullptr)
    {
        return true;
    }

    return CGameManagement::getPlayerInstance()->isDead() || _enemy->isDead();
}

void CBattle::preBattle()
{
    if (_enemy == nullptr)
    {
        return;
    }
    _enemy->preBattle();
    CGameManagement::getPlayerInstance()->preBattle(_enemy);
}

void CBattle::battleLoop()
{
    while (!isBattleOver())
    {
        Console::hr();
        Console::printLnWithSpacer(std::format("Your Hp: {}", CGameManagement::getPlayerInstance()->hpAsString()),
                                   std::format("Enemy Hp: {}", _enemy->hp()));
        Console::hr();
        Console::printLn("New turn");

        _enemy->preBattleAction();

        bool endRound = false;
        std::optional<EWeapons> playersChoice;
        if (doesPlayerGoFirst())
        {
            Console::printLn("You go first");
            playersChoice = CGameManagement::getPlayerInstance()->battleAction(_enemy, endRound);
            _enemy->battleAction(endRound);
        }
        else
        {
            Console::printLn("The enemy is faster.");
            _enemy->battleAction(endRound);
            playersChoice = CGameManagement::getPlayerInstance()->battleAction(_enemy, endRound);
        }
        if (!endRound)
        {
            Console::hr();
            switch (hasWonAgainst(playersChoice, _enemy->peek()))
            {
            case CBattle::EBattleResult::eWon:
                _enemy->dealDamage(CGameManagement::getPlayerInstance()->damage());
                break;
            case CBattle::EBattleResult::eLost:
            {
                Console::printLn("You got hit.");
                CGameManagement::getPlayerInstance()->dealDamage(_enemy->damage());
                break;
            }
            case CBattle::EBattleResult::eTie:
                Console::printLn("It's a tie");
                break;
            }
        }
        if (!_enemy->isDead())
        {
            _enemy->postBattleAction();
        }
    }
}

void CBattle::postBattle()
{
    if (!_enemy->isDead())
    {
        _enemy->postBattle();
    }

    if (CGameManagement::getPlayerInstance()->isDead())
    {
        throw CPlayerDiedException(std::format("The enemy {} was too hard for a weakling like you.", _enemy->name()));
    }

    CGameManagement::getPlayerInstance()->postBattle(_enemy);
}

bool CBattle::doesPlayerGoFirst()
{
    return Randomizer::getRandom(CGameManagement::getPlayerInstance()->initiative() + _enemy->initiative()) <
           CGameManagement::getPlayerInstance()->initiative();
}

CBattle::EBattleResult CBattle::hasWonAgainst(const std::optional<CBattle::EWeapons> choice,
                                              const std::optional<CBattle::EWeapons> other)
{

    if (!choice.has_value() && !other.has_value())
    {
        return CBattle::EBattleResult::eTie;
    }
    if (!choice.has_value() && other.has_value())
    {
        return CBattle::EBattleResult::eLost;
    }
    if (choice.has_value() && !other.has_value())
    {
        return CBattle::EBattleResult::eWon;
    }

    Console::printLnWithSpacer(std::format("[{}Player: {}{}]", CC::fgYellow(), weapon2String(*choice), CC::ccReset()),
                               std::format("[{}Enemy: {}{}]", CC::fgRed(), weapon2String(*other), CC::ccReset()));

    if (*choice == *other)
    {
        return CBattle::EBattleResult::eTie;
    }
    switch (*choice)
    {
    case EWeapons::eRock:
        if (*other == EWeapons::eScissors || *other == EWeapons::eLizard)
        {
            return CBattle::EBattleResult::eWon;
        }
        return CBattle::EBattleResult::eLost;
    case EWeapons::ePaper:
        if (*other == EWeapons::eRock || *other == EWeapons::eSpock)
        {
            return CBattle::EBattleResult::eWon;
        }
        return CBattle::EBattleResult::eLost;
    case EWeapons::eScissors:
        if (*other == EWeapons::ePaper || *other == EWeapons::eLizard)
        {
            return CBattle::EBattleResult::eWon;
        }
        return CBattle::EBattleResult::eLost;
    case EWeapons::eLizard:
        if (*other == EWeapons::eSpock || *other == EWeapons::ePaper)
        {
            return CBattle::EBattleResult::eWon;
        }
        return CBattle::EBattleResult::eLost;
    case EWeapons::eSpock:
        if (*other == EWeapons::eRock || *other == EWeapons::eScissors)
        {
            return CBattle::EBattleResult::eWon;
        }
        return CBattle::EBattleResult::eLost;
    }
    return CBattle::EBattleResult::eTie;
}

std::string CBattle::weapon2String(const EWeapons weapon)
{
    switch (weapon)
    {
    case EWeapons::eRock:
        return "Rock";
    case EWeapons::ePaper:
        return "Paper";
    case EWeapons::eScissors:
        return "Scissors";
    case EWeapons::eLizard:
        return "Lizard";
    case EWeapons::eSpock:
        return "Spock";
    }
    return std::string();
}
