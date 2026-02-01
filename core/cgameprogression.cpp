#include "cgameprogression.h"
#include "cbattleencounter.h"
#include "cdeadhero.h"
#include "cequipmentdealer.h"
#include "cgamemanagement.h"
#include "cmysteriouschest.h"
#include "console.h"
#include "moduleregister.h"
#include "randomizer.h"
#include "translator/ctranslator.h"

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
    ModuleRegister::registerModules(this);
}

void CGameProgression::startGame()
{
    progressToStage(EGameStage::eStart);
}

CGameProgression::CGameProgression() : CGameStateObject("Progression")
{
}

CGameProgression::EGameStage CGameProgression::currentGameStage() const
{
    return _currentStage;
}

std::vector<std::string> CGameProgression::getQuestLog() const
{
    std::vector<std::string> entries;

    for (const auto& m : _registeredModules | std::views::filter(Module::moduleRegisterStageFilter(_currentStage)))
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

bool CGameProgression::areModuleHintsSeen(const std::string_view& moduleName) const
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

bool CGameProgression::moduleHintsAvailable() const
{
    return _moduleHints.size() != 0;
}

void CGameProgression::registerModuleQuest(const std::string_view& moduleName,
                                           const std::string_view& questText,
                                           std::function<void()> questAcceptedFunction)
{

    for (auto& moduleQuest : _moduleQuests | std::views::filter(ModuleQuest::moduleQuestNameFilter(moduleName)))
    {
        moduleQuest.questInfo.questText = questText;
        moduleQuest.accepted = false;
        moduleQuest.questAcceptedFunction = questAcceptedFunction;
        return;
    }

    ModuleQuest quest;
    quest.questInfo.moduleName = moduleName;
    quest.questInfo.questText = questText;
    quest.questAcceptedFunction = questAcceptedFunction;
    _moduleQuests.push_back(quest);
}

void CGameProgression::unregisterModuleQuestByModuleName(const std::string& moduleName)
{
    auto it =
        std::remove_if(_moduleQuests.begin(), _moduleQuests.end(), ModuleQuest::moduleQuestNameFilter(moduleName));
    if (it != _moduleQuests.end())
    {
        _moduleQuests.erase(it);
    }
}

bool CGameProgression::isModuleQuestAccepted(const std::string_view& moduleName) const
{
    return std::count_if(_moduleQuests.begin(),
                         _moduleQuests.end(),
                         [moduleName](const ModuleQuest& quest) {
                             return ModuleQuest::moduleQuestNameFilter(moduleName)(quest) &&
                                    ModuleQuest::moduleQuestAcceptedFilter()(quest);
                         }) != 0;
}

CGameProgression::ModuleQuestInfo CGameProgression::getRandomQuest() const
{
    if (_moduleQuests.size() == 0)
    {
        return {};
    }

    std::vector<ModuleQuest> availableQuests;
    std::copy_if(_moduleQuests.begin(),
                 _moduleQuests.end(),
                 std::back_inserter(availableQuests),
                 ModuleQuest::moduleQuestAvailableFilter());

    if (availableQuests.size() == 0)
    {
        return {};
    }
    return availableQuests.at(Randomizer::getRandom(availableQuests.size())).questInfo;
}

void CGameProgression::acceptModuleQuest(const std::string_view& moduleName)
{
    for (auto& moduleQuest : _moduleQuests | std::views::filter(ModuleQuest::moduleQuestNameFilter(moduleName)))
    {
        moduleQuest.accepted = true;
        moduleQuest.questAcceptedFunction();
        return;
    }
}

bool CGameProgression::areModuleQuestsAvailable() const
{
    return std::any_of(_moduleQuests.begin(), _moduleQuests.end(), ModuleQuest::moduleQuestAvailableFilter()) != 0;
}

bool CGameProgression::isModuleActive(const std::string_view& moduleName) const
{
    for (auto& module : _registeredModules | std::views::filter(Module::moduleRegisterStageFilter(_currentStage)) |
                            std::views::filter(Module::moduleRegisterNameFilter(moduleName)))
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

void CGameProgression::increaseGenocideCount()
{
    _genocideCount++;
}

void CGameProgression::increaseTurns()
{
    _turns++;
}

unsigned int CGameProgression::progress() const
{
    return static_cast<unsigned int>(std::ceil((_finishedModules.size() * 100) / _registeredModules.size()));
}

unsigned long CGameProgression::bodyCount() const
{
    return _bodyCount;
}

unsigned long CGameProgression::genocideCount() const
{
    return _genocideCount;
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
    for (const auto& module : _registeredModules)
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
    for (auto& module : _registeredModules | std::views::filter(Module::moduleRegisterStageFilter(_currentStage)))
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
    for (const auto& module : _registeredModules | std::views::filter(Module::moduleRegisterStageFilter(_currentStage)))
    {
        module.deInitFunction();
        unregisterModuleHintsByModuleName(module.moduleName);
    }

    _currentStage = stage;

    for (const auto& module : _registeredModules | std::views::filter(Module::moduleRegisterStageFilter(_currentStage)))
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
            std::format("But also you learnd, that {} is a huge thing here, which brings you back, to your question:",
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
                                     Ressources::Game::princessLeila()),
                         Console::EAlignment::eCenter);
        break;
    case EGameStage::eFoundCult:
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
                                     Ressources::Game::princessLeila()),
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

    auto it =
        std::find_if(_registeredModules.begin(), _registeredModules.end(), Module::moduleRegisterNameFilter(name));
    if (it != _registeredModules.cend())
    {
        (*it).gameStage = neededForStage;
    }
}

void CGameProgression::registerModule(const Module& module)
{
    _registeredModules.push_back(module);
}

std::string CGameProgression::coreTr(const std::string_view& textId) const
{
    return CTranslator::translate(TagNames::Translator::core, TagNames::Progression::progression, textId);
}

void CGameProgression::registerModule(
    const std::string_view& name,
    const EGameStage neededForStage,
    std::function<std::string()> questLogFunction,
    std::function<void()> initFunction,
    std::function<void()> deInitFunction,
    std::function<void(std::vector<CRoom*>&)> initWorldMapFunction,
    std::function<CSupportCompanion*(const std::string_view& name)> supportCompanionFactory,
    std::function<CRoom*(const std::string_view& name)> roomsFactory,
    std::function<CItem*(const std::string_view& name)> itemFactory,
    std::function<CTask*(const std::string_view& name)> taskFactory)

{
    Module module;
    module.moduleName = name;
    module.gameStage = neededForStage;
    module.questLogFunction = questLogFunction;
    module.initFunction = initFunction;
    module.deInitFunction = deInitFunction;
    module.initWorldMapFunction = initWorldMapFunction;
    module.supportCompantonFactory = supportCompanionFactory;
    module.itemFactory = itemFactory;
    module.roomFactory = roomsFactory;
    module.taskFactory = taskFactory;

    registerModule(module);
}

void CGameProgression::reRegisterModuleForNextStage(const std::string_view& moduleName)
{
    reRegisterModule(moduleName, *(++gameStageIterator(_currentStage)));
}

nlohmann::json CGameProgression::save() const
{
    nlohmann::json o;
    o[TagNames::Progression::currentStage] = _currentStage;
    o[TagNames::Progression::bodyCount] = _bodyCount;
    o[TagNames::Progression::turns] = _turns;
    o[TagNames::Progression::genocideCount] = _genocideCount;

    nlohmann::json finishedModules = nlohmann::json::array();
    for (auto m : _finishedModules)
    {
        finishedModules.push_back(m);
    }
    o[TagNames::Progression::finishedModules] = finishedModules;

    return o;
}

void CGameProgression::load(const nlohmann::json& json)
{
    _turns = json.value<unsigned long>(TagNames::Progression::turns, 0);
    _bodyCount = json.value<unsigned long>(TagNames::Progression::bodyCount, 0);
    _genocideCount = json.value<unsigned long>(TagNames::Progression::genocideCount, 0);

    _currentStage = json.value<EGameStage>(TagNames::Progression::currentStage, EGameStage::eStart);
    for (auto s : gameStageIterator())
    {
        progressToStage(s);
        if (s >= _currentStage)
        {
            break;
        }
    }

    if (json.contains(TagNames::Progression::finishedModules))
    {
        for (auto m : json[TagNames::Progression::finishedModules])
        {
            _finishedModules.push_back(m);
        }
    }
}

CSupportCompanion* CGameProgression::callModuleSupportCompanionFactory(const std::string_view& name)
{
    for (const auto& module : _registeredModules)
    {
        auto companion = module.supportCompantonFactory(name);
        if (companion != nullptr)
        {
            return companion;
        }
    }

    return nullptr;
}

CRoom* CGameProgression::callModuleRoomFactory(const std::string_view& name)
{
    for (const auto& module : _registeredModules)
    {
        auto room = module.roomFactory(name);
        if (room != nullptr)
        {
            return room;
        }
    }

    return nullptr;
}

CTask* CGameProgression::callModuleTaskFactory(const std::string_view& name)
{
    for (const auto& module : _registeredModules)
    {
        auto task = module.taskFactory(name);
        if (task != nullptr)
        {
            return task;
        }
    }

    return nullptr;
}

CItem* CGameProgression::callModuleItemFactory(const std::string_view& name)
{
    for (const auto& module : _registeredModules)
    {
        auto item = module.itemFactory(name);
        if (item != nullptr)
        {
            return item;
        }
    }

    return nullptr;
}
