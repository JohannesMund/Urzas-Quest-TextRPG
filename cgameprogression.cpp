#include "bard/moduleressources.h"
#include "cave/moduleressources.h"
#include "lakeoftears/moduleressources.h"
#include "layla/moduleressources.h"
#include "ratfarm/moduleressources.h"
#include "sewer/moduleressources.h"

#include "cbattleencounter.h"
#include "cdeadhero.h"
#include "cequipmentdealer.h"
#include "cmysteriouschest.h"

#include "cgamemanagement.h"
#include "cgameprogression.h"
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
    CGameManagement::getInstance()->registerEncounter(new CEquipmentDealer());

    registerModule(BardRessources::moduleName(), EGameStage::eStart);

    registerModule(RatFarmRessources::moduleName(), EGameStage::eSeenBard);
    registerModule(CaveRessources::moduleName(), EGameStage::eSeenBard);

    registerModule(LakeTearsRessources::moduleName(), EGameStage::eProvenAsHero);
    registerModule(LaylaRessources::moduleName(), EGameStage::eProvenAsHero);
    registerModule(SewerRessources::moduleName(), EGameStage::eProvenAsHero);

    progressToStage(EGameStage::eStart);
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
    if (is(LakeTearsRessources::moduleName()))
    {
        LakeTearsRessources::initModule();
        return;
    }
    if (is(SewerRessources::moduleName()))
    {
        SewerRessources::initModule();
        return;
    }
    if (is(LaylaRessources::moduleName()))
    {
        LaylaRessources::initModule();
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
    if (is(LakeTearsRessources::moduleName()))
    {
        LakeTearsRessources::deInitModule();
        return;
    }
    if (is(SewerRessources::moduleName()))
    {
        SewerRessources::deInitModule();
        return;
    }
    if (is(LaylaRessources::moduleName()))
    {
        LaylaRessources::deInitModule();
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
        return;
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
        Console::printLn(Ressources::Game::whoTheFuckIsUrza());
        Console::br();
        Console::printLn("You will have to find out.");
        break;
    case EGameStage::eProvenAsHero:
        Console::printLn("Chapter 2", Console::EAlignment::eCenter);
        Console::br();
        Console::printLn("Now you know, what it means to be a hero. You have proven yourself worthy.");
        Console::printLn(
            std::format("But also know, that {} is a huge thing here, which brings you back, to your question:",
                        Ressources::Game::urza()));
        Console::br();
        Console::printLn(Ressources::Game::whoTheFuckIsUrza());
        Console::br();
        Console::printLn("Well, you are getting closer.");
        break;
    case EGameStage::eLearnedAboutCult:
        Console::printLn("Chapter 3", Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(
            std::format("Urza {0} is a huge thing, and the cult of {0} as well.", Ressources::Game::urza()));
        Console::br();
        Console::printLn(
            std::format("But who the fuck are {} and {}", Ressources::Game::fiego(), Ressources::Game::brock()));
        Console::br();
        Console::printLn(std::format("But your goal is clearer than before: Marry {}, or find a good tattoo remover.",
                                     Ressources::Game::princessLayla()));
        break;

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
