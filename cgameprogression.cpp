#include "bard/moduleressources.h"
#include "cave/moduleressources.h"
#include "ratfarm/moduleressources.h"

#include "cbattleencounter.h"
#include "cdeadhero.h"
#include "cgamemanagement.h"
#include "cgameprogression.h"
#include "cmysteriouschest.h"
#include "console.h"

#include <algorithm>
#include <format>

void CGameProgression::initEncounters()
{
    CGameManagement::getInstance()->registerEncounter(new CMysteriousChest());
    CGameManagement::getInstance()->registerEncounter(new CDeadHero());
    CGameManagement::getInstance()->registerEncounter(new CBattleEncounter());

    BardRessources::initModule();
}

CGameProgression::CGameProgression()
{
}

CGameProgression::EGameStage CGameProgression::currentGameStage() const
{
    return _currentStage;
}

void CGameProgression::progress()
{
    if (!canProgress())
    {
        return;
    }

    switch (_currentStage)
    {
    case EGameStage::eStart:
        BardRessources::deInitModule();
        progressToStage(EGameStage::eSeenBard);
        RatFarmRessources::initModule();
        CaveRessources::initModule();
        return;
    case EGameStage::eSeenBard:
        RatFarmRessources::deInitModule();
        CaveRessources::deInitModule();
        progressToStage(EGameStage::eProvenAsHero);
        return;
    case EGameStage::eProvenAsHero:
    case EGameStage::eLearnedAboutCult:
    default:
        return;
    }
}

void CGameProgression::reportModuleFinished(const std::string_view& moduleName)
{
    _finishedModules.push_back(std::string(moduleName));
}

bool CGameProgression::isModuleFinished(const std::string_view& moduleName)
{
    return std::find(_finishedModules.begin(), _finishedModules.end(), moduleName) != _finishedModules.end();
}

bool CGameProgression::canProgress()
{
    switch (_currentStage)
    {
    case EGameStage::eStart:
        if (!isModuleFinished(BardRessources::moduleName()))
        {
            return false;
        }
        return true;
    case EGameStage::eProvenAsHero:
        if (!isModuleFinished(CaveRessources::moduleName()))
        {
            return false;
        }
        if (!isModuleFinished(RatFarmRessources::moduleName()))
        {
            return false;
        }
        return true;
    case EGameStage::eLearnedAboutCult:
    default:
        return false;
    }
}

void CGameProgression::progressToStage(EGameStage stage)
{
    _currentStage = stage;
    Console::cls();

    switch (_currentStage)
    {
    case EGameStage::eStart:
    case EGameStage::eSeenBard:
        Console::printLn("Chapter 1", Console::EAlignment::eCenter);
        Console::br();
        Console::printLn("You have seen quite some things, since you awoke in this strange world.");
        Console::printLn("At least, you have 2 things:");
        Console::printLn(
            std::format("The matching {} for the {},", Ressources::Items::sock(), Ressources::Items::otherSock()));
        Console::printLn(
            std::format("and you have a task. You cannot stop thinking about the song of the {} and the question:",
                        BardRessources::encounterName()));
        Console::br();
        Console::printLn(Ressources::whoTheFuckIsUrza());
        Console::br();
        Console::printLn("You will have to find out.");
        break;
    case EGameStage::eProvenAsHero:
    case EGameStage::eLearnedAboutCult:
    default:
        break;
    }
    Console::confirmToContinue();
}
