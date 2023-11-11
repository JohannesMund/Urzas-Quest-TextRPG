#pragma once

#include <optional>
#include <string>

class CEnemy;
class CBattle
{
public:
    enum class EWeapons
    {
        eRock,
        ePaper,
        eScissors,
        eLizard,
        eSpock
    };

    static std::string weapon2String(const EWeapons weapon);

    enum class EBattleResult
    {
        eWon,
        eLost,
        eTie
    };

    CBattle();
    CBattle(CEnemy* enemy);

    void fight();

private:
    bool isBattleOver() const;

    void preBattle();
    void battleLoop();
    void postBattle();

    bool doesPlayerGoFirst();

    static EBattleResult hasWonAgainst(const std::optional<EWeapons> choice, const std::optional<EWeapons> other);

    CEnemy* _enemy = nullptr;
};
