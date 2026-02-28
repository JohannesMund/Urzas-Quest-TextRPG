#include "cdjinncompanion.h"

#include "cenemy.h"
#include "cgamemanagement.h"
#include "cnpc.h"
#include "console.h"
#include "randomizer.h"
#include "wonderlamp/moduleressources.h"

CDjinnCompanion::CDjinnCompanion(const CNpc* npc) :
    CSupportCompanion(WonderLamp::moduleName(), TagNames::WonderLamp::djinnCompanion),
    _djinn(npc)
{
}

std::string CDjinnCompanion::name() const
{
    return _djinn->name();
}

std::string CDjinnCompanion::type() const
{
    return Ressources::Companion::typeAsString(Ressources::Companion::ECompanionType::eScaryMonster);
}

void CDjinnCompanion::battleAction(CEnemy* enemy, bool&)
{
    if (_djinn->sympathy() > CNpc::ESympathyLevel::eNeutral)
    {
        Console::printLn(tr("{} is going all out and attacks relentlessly", _djinn->name()));
        enemy->dealDamage(1 + Randomizer::getRandom(2));
    }
    else
    {
        enemy->dealDamage(2);
    }
}

void CDjinnCompanion::postBattle(CEnemy* enemy)
{
    Console::printLn(
        tr("The battle is done, {} bows in front of you after {} has been defeated and your wish has been fulfilled.",
           _djinn->name(),
           enemy->name()));
    CGameManagement::getPlayerInstance()->removeSupporCompanionsByName(_djinn->name(), false);
}

int CDjinnCompanion::shield(const int i)
{
    if (_djinn->sympathy() >= CNpc::ESympathyLevel::eLove)
    {
        Console::printLn(tr("{} fights like a bezerk at your side, risking {} own live tanking hits aimed at you",
                            _djinn->name(),
                            _djinn->hisHer()));
        return i - 2;
    }
    if (_djinn->sympathy() < CNpc::ESympathyLevel::eNeutral)
    {
        Console::printLn(tr("{} Does not really care about you getting hit", _djinn->name()));
    }
    if (_djinn->sympathy() == CNpc::ESympathyLevel::eHate)
    {
        Console::printLn(tr("Actually, {} seems to laught at you, while you are taking damage.", _djinn->heShe()));
    }
    return 0;
}

void CDjinnCompanion::joinText() const
{
    Console::printLn(
        tr("{} Pops out of is bottle with a lout \"Woosh\" and joins your side in battle.", _djinn->name()));
}

void CDjinnCompanion::leaveText() const
{
    Console::printLn(tr("{} returns into {} bottle with a \"Slurp\" sound. Your should visit {} again soon.",
                        _djinn->name(),
                        _djinn->hisHer(),
                        _djinn->himHer()));
}
