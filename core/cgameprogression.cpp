#include "cgameprogression.h"
#include "cbattleencounter.h"
#include "cdeadhero.h"
#include "cequipmentdealer.h"
#include "cgamemanagement.h"
#include "cmysteriouschest.h"
#include "console.h"
#include "randomizer.h"

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
}

void CGameProgression::initModules()
{
    for (auto& module : ModuleRegister::registerModules())
    {
        registerModule(module);
    }
}

void CGameProgression::startGame()
{
    progressToStage(Ressources::Game::EGameStage::eStart);
}

CGameProgression::CGameProgression()
{
}

Ressources::Game::EGameStage CGameProgression::currentGameStage() const
{
    return _currentStage;
}

std::vector<std::string> CGameProgression::getQuestLog() const
{
    std::vector<std::string> entries;

    for (const auto& m :
         _moduleRegister | std::views::filter(ModuleRegister::Module::moduleRegisterStageFilter(_currentStage)))
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

void CGameProgression::checkGameProgress()
{
    if (!canProgress())
    {
        return;
    }

    gameStageIterator it = _currentStage;
    progressToStage(*(++it));
}

void CGameProgression::reportModuleFinished(const std::string_view& moduleName)
{
    if (isModuleFinished(moduleName))
    {
        return;
    }

    _finishedModules.push_back(std::string(moduleName));
}

void CGameProgression::registerModuleHint(const std::string_view& moduleName, const std::string_view& hintText)
{
    ModuleHint hint;
    hint.moduleName = moduleName;
    hint.hintText = hintText;

    _moduleHints.push_back(hint);
}

void CGameProgression::unregisterModuleHintsByModuleName(const std::string& moduleName)
{
    auto it = std::remove_if(_moduleHints.begin(), _moduleHints.end(), ModuleHint::moduleHintNameFilter(moduleName));
    if (it != _moduleHints.end())
    {
        _moduleHints.erase(it);
    }
}

bool CGameProgression::seenModuleHints(const std::string_view& moduleName)
{
    bool seen = false;
    for (auto& moduleHint : _moduleHints | std::views::filter(ModuleHint::moduleHintNameFilter(moduleName)))
    {
        if (moduleHint.seen == false)
        {
            return false;
        }
        else
        {
            seen = true;
        }
    }

    return seen;
}

std::string CGameProgression::getRandomHint()
{
    if (_moduleHints.size() == 0)
    {
        return {};
    }

    auto index = Randomizer::getRandom(_moduleHints.size());
    _moduleHints.at(index).seen = true;
    return _moduleHints.at(index).hintText;
}

bool CGameProgression::isModuleActive(const std::string_view& moduleName) const
{
    for (auto& module : _moduleRegister |
                            std::views::filter(ModuleRegister::Module::moduleRegisterStageFilter(_currentStage)) |
                            std::views::filter(ModuleRegister::Module::moduleRegisterNameFilter(moduleName)))
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

void CGameProgression::increaseTurns()
{
    _turns++;
}

unsigned int CGameProgression::progress() const
{
    return std::ceil((_finishedModules.size() * 100) / _moduleRegister.size());
}

unsigned long CGameProgression::bodyCount() const
{
    return _bodyCount;
}

unsigned long CGameProgression::turns() const
{
    return _turns;
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
    for (auto& module :
         _moduleRegister | std::views::filter(ModuleRegister::Module::moduleRegisterStageFilter(_currentStage)))
    {
        if (!isModuleFinished(module.moduleName))
        {
            return false;
        }
    }
    return true;
}

void CGameProgression::progressToStage(Ressources::Game::EGameStage stage)
{
    for (const auto& module :
         _moduleRegister | std::views::filter(ModuleRegister::Module::moduleRegisterStageFilter(_currentStage)))
    {
        module.deInitFunction();
        unregisterModuleHintsByModuleName(module.moduleName);
    }

    _currentStage = stage;
    reRegisterModule(Ressources::Game::ShrineRessources::moduleName(), _currentStage);

    for (const auto& module :
         _moduleRegister | std::views::filter(ModuleRegister::Module::moduleRegisterStageFilter(_currentStage)))
    {
        module.initFunction();
    }

    Console::cls(false);
    Console::hr();
    switch (_currentStage)
    {
    case Ressources::Game::EGameStage::eStart:
        return;
    case Ressources::Game::EGameStage::eSeenBard:
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
    case Ressources::Game::EGameStage::eProvenAsHero:
        Console::printLn("Chapter 2", Console::EAlignment::eCenter);
        Console::br();
        Console::printLn("Now you know, what it means to be a hero. You have proven yourself worthy.",
                         Console::EAlignment::eCenter);
        Console::printLn(
            std::format("But also you learnd, that {} is a huge thing here, which brings you back, to your question:",
                        Ressources::Game::urza()),
            Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(Ressources::Game::whoTheFuckIsUrza(), Console::EAlignment::eCenter);
        Console::br();
        Console::printLn("Well, you are getting closer.", Console::EAlignment::eCenter);
        break;
    case Ressources::Game::EGameStage::eLearnedAboutCult:
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
    case Ressources::Game::EGameStage::eFoundCult:
        Console::printLn("Chapter 4", Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(std::format("Here you are. Proud Memner of the Rebellion.", Ressources::Game::urza()),
                         Console::EAlignment::eCenter);
        Console::br();

        Console::printLn("Now you only have to find out:", Console::EAlignment::eCenter);
        Console::printLn("Why do we rebel?", Console::EAlignment::eCenter);
        Console::printLn("Against whom do we rebel?", Console::EAlignment::eCenter);
        Console::printLn("of course:", Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(Ressources::Game::whoTheFuckIsUrza(), Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(std::format("And last not least, is ist right to kidnap {}, and when do we do it?",
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

void CGameProgression::reRegisterModule(const std::string_view& name, const Ressources::Game::EGameStage neededForStage)
{
    unFinishModule(name);

    auto it = std::find_if(
        _moduleRegister.begin(), _moduleRegister.end(), ModuleRegister::Module::moduleRegisterNameFilter(name));
    if (it != _moduleRegister.cend())
    {
        (*it).gameStage = neededForStage;
    }
}

void CGameProgression::registerModule(const ModuleRegister::Module& module)
{
    _moduleRegister.push_back(module);
}
