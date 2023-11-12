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
#include <cmath>
#include <format>
#include <ranges>
#include <utility>

void CGameProgression::initEncounters()
{
    CGameManagement::getInstance()->registerEncounter(new CMysteriousChest());
    CGameManagement::getInstance()->registerEncounter(new CDeadHero());
    CGameManagement::getInstance()->registerEncounter(new CBattleEncounter());

    registerModule(BardRessources::moduleName(), EGameStage::eStart);

    registerModule(RatFarmRessources::moduleName(), EGameStage::eSeenBard);
    registerModule(CaveRessources::moduleName(), EGameStage::eSeenBard);
    registerModule(Ressources::Game::ShrineRessources::moduleName(), EGameStage::eSeenBard);

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
        progressToStage(EGameStage::eSeenBard);
        return;
    case EGameStage::eSeenBard:
        progressToStage(EGameStage::eProvenAsHero);
        return;
    case EGameStage::eProvenAsHero:
        progressToStage(EGameStage::eLearnedAboutCult);
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

unsigned int CGameProgression::getProgress() const
{
    return std::ceil((_finishedModules.size() * 100) / _modulesForStage.size());
}

unsigned int CGameProgression::getBodyCount() const
{
    return _bodyCount;
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

void CGameProgression::initModuleByName(const std::string_view& moduleName)
{
    auto is = [&moduleName](const std::string_view& s) { return moduleName.compare(s) == 0; };

    if (is(BardRessources::moduleName()))
    {
        BardRessources::initModule();
        return;
    }
    if (is(CaveRessources::moduleName()))
    {
        CaveRessources::initModule();
        return;
    }
    if (is(RatFarmRessources::moduleName()))
    {
        RatFarmRessources::initModule();
        return;
    }
}

void CGameProgression::deInitModuleByName(const std::string_view& moduleName)
{
    auto is = [&moduleName](const std::string_view& s) { return moduleName.compare(s) == 0; };

    if (is(BardRessources::moduleName()))
    {
        BardRessources::deInitModule();
        return;
    }
    if (is(CaveRessources::moduleName()))
    {
        CaveRessources::deInitModule();
        return;
    }
    if (is(RatFarmRessources::moduleName()))
    {
        RatFarmRessources::deInitModule();
        return;
    }
}

bool CGameProgression::canProgress()
{

    for (auto module : _modulesForStage | std::views::filter(modPairStageFilter(_currentStage)))
    {
        if (!isModuleFinished(module.first))
        {
            return false;
        }
    }
    return true;
}

void CGameProgression::progressToStage(EGameStage stage)
{
    for (auto module : _modulesForStage | std::views::filter(modPairStageFilter(_currentStage)))
    {
        deInitModuleByName(module.first);
    }

    _currentStage = stage;
    reRegisterModule(Ressources::Game::ShrineRessources::moduleName(), _currentStage);

    for (auto module : _modulesForStage | std::views::filter(modPairStageFilter(_currentStage)))
    {
        initModuleByName(module.first);
    }

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

void CGameProgression::reRegisterModule(const std::string_view& name, const EGameStage neededForStage)
{
    unFinishModule(name);
    registerModule(name, neededForStage);
}

void CGameProgression::registerModule(const std::string_view& name, const EGameStage neededForStage)
{
    auto it = std::find_if(_modulesForStage.begin(), _modulesForStage.end(), modPairNameFilter(name));
    if (it != _modulesForStage.cend())
    {
        (*it).second = neededForStage;
    }
    else
    {
        _modulesForStage.push_back(std::make_pair(std::string(name), neededForStage));
    }
}

std::function<bool(const std::pair<std::string, CGameProgression::EGameStage>&)> CGameProgression::modPairNameFilter(
    const std::string_view& name)
{
    return [&name](const auto modPair) { return modPair.first.compare(name) == 0; };
}

std::function<bool(const std::pair<std::string, CGameProgression::EGameStage>&)> CGameProgression::modPairStageFilter(
    const EGameStage& stage)
{
    return [&stage](auto module) { return module.second == stage; };
}