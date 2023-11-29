#pragma once

#include "enumiterator.h"

#include <functional>
#include <string>
#include <vector>

class CRoom;
class CGameProgression
{
    friend class CGameManagement;

public:
    enum class EGameStage
    {
        eNone,
        eStart,
        eSeenBard,
        eProvenAsHero,
        eLearnedAboutCult,
        eFoundCult,
        eFoundUrza,
        eFinale
    };

    EGameStage currentGameStage() const;
    std::vector<std::string> getQuestLog() const;

    void reportModuleFinished(const std::string_view& moduleName);

    void registerModuleHint(const std::string_view& moduleName, const std::string_view& hint);
    void unregisterModuleHintsByModuleName(const std::string& moduleName);
    bool seenModuleHints(const std::string_view& moduleName);
    std::string getRandomHint();

    bool isModuleActive(const std::string_view& moduleName) const;
    bool isModuleFinished(const std::string_view& moduleName) const;

    void increaseBodyCount();
    void increaseTurns();

    unsigned int progress() const;
    unsigned long bodyCount() const;
    unsigned long turns() const;

private:
    typedef EnumIterator<EGameStage, EGameStage::eNone, EGameStage::eFinale> gameStageIterator;

    struct ModuleRegister
    {
        std::string moduleName;
        EGameStage gameStage;
        std::function<std::string()> questLogFunction;
        std::function<void()> initFunction;
        std::function<void()> deInitFunction;
        std::function<void(std::vector<CRoom*>&)> initWorldMapFunction;

        static std::function<bool(const ModuleRegister)> moduleRegisterNameFilter(const std::string_view& name)
        {
            return [name](const auto module) { return module.moduleName.compare(name) == 0; };
        }
        static std::function<bool(const ModuleRegister)> moduleRegisterStageFilter(const EGameStage& stage)
        {
            return [stage](auto module) { return module.gameStage == stage; };
        }

        static void noInitDeInitFunction()
        {
        }
        static void noInitWorldMapFunction(std::vector<CRoom*>&)
        {
        }
        static std::string noQuestLogFunction()
        {
            return std::string{};
        }
    };

    struct ModuleHint
    {
        std::string moduleName;
        std::string hintText;
        bool seen = false;
        static std::function<bool(const ModuleHint)> moduleHintNameFilter(const std::string_view& name)
        {
            return [name](const auto hint) { return hint.moduleName.compare(name) == 0; };
        }
    };

    CGameProgression();

    void initEncounters();
    void initModules();
    void startGame();

    void checkGameProgress();

    void unFinishModule(const std::string_view& moduleName);

    void initModuleByName(const std::string_view& moduleName);
    void deInitModuleByName(const std::string_view& moduleName);

    bool canProgress();

    void deInitStage();
    void initStage();
    void initWorldMap(std::vector<CRoom*>& rooms) const;

    void progressToStage(EGameStage stage);

    void reRegisterModule(const std::string_view& name, const EGameStage neededForStage);
    void registerModule(
        const std::string_view& name,
        const EGameStage neededForStage,
        std::function<std::string()> questLogFunction = &ModuleRegister::noQuestLogFunction,
        std::function<void()> initFunction = &ModuleRegister::noInitDeInitFunction,
        std::function<void()> deInitFunction = &ModuleRegister::noInitDeInitFunction,
        std::function<void(std::vector<CRoom*>&)> initWorldMapFunction = &ModuleRegister::noInitWorldMapFunction);

    EGameStage _currentStage = EGameStage::eNone;
    unsigned long _bodyCount = 0;
    unsigned long _turns = 0;

    std::vector<std::string> _finishedModules;
    std::vector<ModuleRegister> _moduleRegister;
    std::vector<ModuleHint> _moduleHints;
};
