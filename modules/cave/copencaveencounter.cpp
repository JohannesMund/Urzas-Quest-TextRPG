#include "copencaveencounter.h"
#include "cave/moduleressources.h"
#include "ccave.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "copencavetask.h"
#include "cshaggyssandwich.h"

#include <format>

COpenCaveEncounter::COpenCaveEncounter()
{
    _isSingleExecution = true;
    _type = CEncounter::eField;
}

void COpenCaveEncounter::execute(const std::string_view& moduleName)
{
    CEncounter::execute(moduleName);
    _hasBeenExecuted = true;
    CGameManagement::getInstance()->placeTask(new COpenCaveTask(), CCave::caveFilter());

    Console::printLn("A tall, lanky guy, and a dog. Screaming. Running in your direction, followed by a cloud of dust, "
                     "stirred up by them. Their faces are marked with sheer panic.");
    Console::printLn(
        "\"Mo-mo-mo-mo-moooonsteeeer\" screems the guy. \"C-c-c-c-aaaaaaave\" screams the dog. Yes, this dog can talk. "
        "what a world, that you are living in! (Did I mention the gigantic sandwich, the guy carries? no? anyone?). "
        "Appearently, you did well in not entering the cave up to now.");
    CGameManagement::getInventoryInstance()->addItem(new CShaggysSandwich);
}

unsigned int COpenCaveEncounter::encounterChance(const EEncounterType& tp, const std::string_view& moduleName) const
{
    return 5;
}

std::string COpenCaveEncounter::name() const
{
    return std::format(
        "{0}Scr{1}amm{2}ing {1}Cow{0}ards{3}", CC::fgYellow(), CC::fgLightGreen(), CC::fgWhite(), CC::ccReset());
}

std::string COpenCaveEncounter::moduleName() const
{
    return CaveRessources::moduleName();
}
