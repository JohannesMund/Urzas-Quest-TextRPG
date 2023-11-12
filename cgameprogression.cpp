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

    _currentStage = EGameStage::eStart;
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
    if (isModuleFinished(moduleName))
    {
        return;
    }

    _finishedModules.push_back(std::string(moduleName));
}

void CGameProgression::increaseBodyCount()
{
    _bodyCount++;
}

bool CGameProgression::isModuleFinished(const std::string_view& moduleName)
{
    return std::find(_finishedModules.begin(), _finishedModules.end(), moduleName) != _finishedModules.end();
}

void CGameProgression::unFinishModule(const std::string_view& moduleName)
{
    auto it = std::find(_finishedModules.begin(), _finishedModules.end(), moduleName);
    if (it != _finishedModules.end())
    {
        _finishedModules.erase(it);
    }
}

bool CGameProgression::canProgress()
{
    switch (_currentStage)
    {
    case EGameStage::eStart:
        if (isModuleFinished(BardRessources::moduleName()) &&
            isModuleFinished(Ressources::Game::ShrineRessources::moduleName()) && _bodyCount > 10)
        {
            return true;
        }
        return false;

    case EGameStage::eProvenAsHero:
        if (isModuleFinished(CaveRessources::moduleName()) && isModuleFinished(RatFarmRessources::moduleName()) &&
            isModuleFinished(Ressources::Game::ShrineRessources::moduleName()))
        {
            return true;
        }
        return false;
    case EGameStage::eLearnedAboutCult:
    default:
        return false;
    }
}

void CGameProgression::progressToStage(EGameStage stage)
{
    _currentStage = stage;
    unFinishModule(Ressources::Game::ShrineRessources::moduleName());

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
