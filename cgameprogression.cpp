#include "bard/moduleressources.h"
#include "cave/moduleressources.h"
#include "fishingvillage/moduleressources.h"
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

    registerModule(Ressources::Game::ShrineRessources::moduleName(), EGameStage::eStart);

    registerModule(BardRessources::moduleName(),
                   EGameStage::eStart,
                   &BardRessources::questLog,
                   &BardRessources::initModule,
                   &BardRessources::deInitModule);

    registerModule(FishingVillageRessources::moduleNameMakeRod(),
                   EGameStage::eSeenBard,
                   &FishingVillageRessources::questLogMakeRod,
                   &FishingVillageRessources::initModuleMakeRod,
                   &ModuleRegister::noInitDeInitFunction,
                   &FishingVillageRessources::initWorldMap);
    registerModule(RatFarmRessources::moduleName(),
                   EGameStage::eSeenBard,
                   &RatFarmRessources::questLog,
                   &RatFarmRessources::initModule,
                   &RatFarmRessources::deInitModule);
    registerModule(CaveRessources::moduleName(),
                   EGameStage::eSeenBard,
                   &CaveRessources::questLog,
                   &CaveRessources::initModule,
                   &CaveRessources::deInitModule,
                   &CaveRessources::initWorldMap);

    registerModule(FishingVillageRessources::moduleNameMakeBoat(),
                   EGameStage::eProvenAsHero,
                   &FishingVillageRessources::questLogMAkeBoat,
                   &FishingVillageRessources::initModuleMakeBoat);
    registerModule(LakeTearsRessources::moduleName(),
                   EGameStage::eProvenAsHero,
                   &LakeTearsRessources::questLog,
                   &LakeTearsRessources::initModule,
                   &LakeTearsRessources::deInitModule);
    registerModule(LaylaRessources::moduleName(),
                   EGameStage::eProvenAsHero,
                   &LaylaRessources::questLog,
                   &LaylaRessources::initModule,
                   &LaylaRessources::deInitModule);
    registerModule(SewerRessources::moduleName(),
                   EGameStage::eProvenAsHero,
                   &SewerRessources::questLog,
                   &SewerRessources::initModule,
                   &SewerRessources::deInitModule);

    registerModule(FishingVillageRessources::moduleNameFishLegend(),
                   EGameStage::eLearnedAboutCult,
                   &FishingVillageRessources::questLogFishLegend,
                   &FishingVillageRessources::initModuleFishLegend);

    progressToStage(EGameStage::eStart);
}

CGameProgression::CGameProgression()
{
}

CGameProgression::EGameStage CGameProgression::currentGameStage() const
{
    return _currentStage;
}

std::vector<std::string> CGameProgression::getQuestLog() const
{
    std::vector<std::string> entries;

    for (const auto& m : _moduleRegister | std::views::filter(ModuleRegister::moduleRegisterStageFilter(_currentStage)))
    {
        auto log = m.questLogFunction();
        if (log.empty())
        {
            continue;
        }
        if (isModuleFinished(m.moduleName))
        {
            log = std::format("[{}Done{}] {}", CC::fgLightGreen(), CC::ccReset(), log);
        }
        else
        {
            log = std::format("[    ] {}", log);
        }
        entries.push_back(log);
    }
    return entries;
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

bool CGameProgression::isModuleActive(const std::string_view& moduleName) const
{
    for (auto& module : _moduleRegister | std::views::filter(ModuleRegister::moduleRegisterStageFilter(_currentStage)) |
                            std::views::filter(ModuleRegister::moduleRegisterNameFilter(moduleName)))
    {
        if (isModuleFinished(module.moduleName))
        {
            return false;
        }
        return true;
    }
    return false;
}

void CGameProgression::increaseBodyCount()
{
    _bodyCount++;
}

unsigned int CGameProgression::getProgress() const
{
    return std::ceil((_finishedModules.size() * 100) / _moduleRegister.size());
}

unsigned int CGameProgression::getBodyCount() const
{
    return _bodyCount;
}

bool CGameProgression::isModuleFinished(const std::string_view& moduleName) const
{
    return std::find(_finishedModules.begin(), _finishedModules.end(), moduleName) != _finishedModules.end();
}

void CGameProgression::initWorldMap(std::vector<CRoom*>& rooms) const
{
    for (const auto& module : _moduleRegister)
    {
        module.initWorldMapFunction(rooms);
    }
}

void CGameProgression::unFinishModule(const std::string_view& moduleName)
{
    auto it = std::remove(_finishedModules.begin(), _finishedModules.end(), moduleName);
    if (it != _finishedModules.end())
    {
        _finishedModules.erase(it);
    }
}

bool CGameProgression::canProgress()
{
    for (auto& module : _moduleRegister | std::views::filter(ModuleRegister::moduleRegisterStageFilter(_currentStage)))
    {
        if (!isModuleFinished(module.moduleName))
        {
            return false;
        }
    }
    return true;
}

void CGameProgression::progressToStage(EGameStage stage)
{
    for (const auto& module :
         _moduleRegister | std::views::filter(ModuleRegister::moduleRegisterStageFilter(_currentStage)))
    {
        module.deInitFunction();
    }

    _currentStage = stage;
    reRegisterModule(Ressources::Game::ShrineRessources::moduleName(), _currentStage);

    for (const auto& module :
         _moduleRegister | std::views::filter(ModuleRegister::moduleRegisterStageFilter(_currentStage)))
    {
        module.initFunction();
    }

    Console::cls(false);
    Console::hr();
    switch (_currentStage)
    {
    case EGameStage::eStart:
        return;
    case EGameStage::eSeenBard:
        Console::printLn("Chapter 1", Console::EAlignment::eCenter);
        Console::hr();
        Console::printLn("You have seen quite some things, since you awoke in this strange world.",
                         Console::EAlignment::eCenter);
        Console::printLn("At least, you have 2 things:", Console::EAlignment::eCenter);
        Console::printLn(
            std::format("The matching {} for the {},", Ressources::Items::otherSock(), Ressources::Items::sock()),
            Console::EAlignment::eCenter);
        Console::printLn(
            std::format("and you have a task. You cannot stop thinking about the song of the {} and the question:",
                        BardRessources::encounterName()),
            Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(Ressources::Game::whoTheFuckIsUrza(), Console::EAlignment::eCenter);
        Console::br();
        Console::printLn("You will have to find out.", Console::EAlignment::eCenter);
        break;
    case EGameStage::eProvenAsHero:
        Console::printLn("Chapter 2", Console::EAlignment::eCenter);
        Console::br();
        Console::printLn("Now you know, what it means to be a hero. You have proven yourself worthy.",
                         Console::EAlignment::eCenter);
        Console::printLn(
            std::format("But also you learnde, that {} is a huge thing here, which brings you back, to your question:",
                        Ressources::Game::urza()),
            Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(Ressources::Game::whoTheFuckIsUrza(), Console::EAlignment::eCenter);
        Console::br();
        Console::printLn("Well, you are getting closer.", Console::EAlignment::eCenter);
        break;
    case EGameStage::eLearnedAboutCult:
        Console::printLn("Chapter 3", Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(
            std::format("Urza {0} is a huge thing, and the cult of {0} as well.", Ressources::Game::urza()),
            Console::EAlignment::eCenter);
        Console::br();

        Console::printLn("But where there was one question, ther are now three:", Console::EAlignment::eCenter);
        Console::printLn(std::format("who the hell is {}?", Ressources::Game::fiego()), Console::EAlignment::eCenter);
        Console::printLn(std::format("who in the world is {}?", Ressources::Game::brock()),
                         Console::EAlignment::eCenter);
        Console::printLn("And of course:", Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(Ressources::Game::whoTheFuckIsUrza(), Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(std::format("But your goal is clearer than before: Marry {}, or find a good tattoo remover.",
                                     Ressources::Game::princessLayla()),
                         Console::EAlignment::eCenter);
        break;

    default:
        break;
    }

    Console::hr();
    Console::br();
    Console::confirmToContinue();
}

void CGameProgression::reRegisterModule(const std::string_view& name, const EGameStage neededForStage)
{
    unFinishModule(name);
    registerModule(name, neededForStage, {}, {}, {});
}

void CGameProgression::registerModule(const std::string_view& name,
                                      const EGameStage neededForStage,
                                      std::function<std::string()> questLogFunction,
                                      std::function<void()> initFunction,
                                      std::function<void()> deInitFunction,
                                      std::function<void(std::vector<CRoom*>&)> initWorldMapFunction)
{
    auto it =
        std::find_if(_moduleRegister.begin(), _moduleRegister.end(), ModuleRegister::moduleRegisterNameFilter(name));
    if (it != _moduleRegister.cend())
    {
        (*it).gameStage = neededForStage;
    }
    else
    {
        ModuleRegister module;
        module.moduleName = name;
        module.gameStage = neededForStage;
        module.questLogFunction = questLogFunction;
        module.initFunction = initFunction;
        module.deInitFunction = deInitFunction;
        module.initWorldMapFunction = initWorldMapFunction;

        _moduleRegister.push_back(module);
    }
}
