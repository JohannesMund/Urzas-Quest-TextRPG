#pragma once

#include "cgamestateobject.h"
#include "enumiterator.h"
#include "ressources.h"

#include <functional>
#include <string>
#include <vector>

class CRoom;
class CSupportCompanion;
class CItem;
class CTask;
class CGameProgression : public CGameStateObject
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

    struct ModuleQuestInfo
    {
        std::string moduleName;
        std::string questText;
    };

    static void noInitDeInitFunction()
    {
    }
    static void noInitWorldMapFunction(std::vector<CRoom*>&)
    {
    }
    static CSupportCompanion* noSupportCompanionFactory(const std::string_view&)
    {
        return nullptr;
    }
    static CRoom* noRoomFactory(const std::string_view&)
    {
        return nullptr;
    }
    static CItem* noItemFactory(const std::string_view&)
    {
        return nullptr;
    }
    static CTask* noTaskFactory(const std::string_view&)
    {
        return nullptr;
    }

    static std::string noQuestLogFunction()
    {
        return std::string{};
    }

    EGameStage currentGameStage() const;
    std::vector<std::string> getQuestLog() const;

    void reportModuleFinished(const std::string_view& moduleName);

    void registerModuleHint(const std::string_view& moduleName, const std::string_view& hint);
    void unregisterModuleHintsByModuleName(const std::string& moduleName);
    bool areModuleHintsSeen(const std::string_view& moduleName) const;
    std::string getRandomHint();
    bool moduleHintsAvailable() const;

    void registerModuleQuest(const std::string_view& moduleName,
                             const std::string_view& questText,
                             std::function<void()> questAcceptedFunction = ModuleQuest::noQuestAcceptedFunction());

    void unregisterModuleQuestByModuleName(const std::string& moduleName);
    bool isModuleQuestAccepted(const std::string_view& moduleName) const;
    ModuleQuestInfo getRandomQuest() const;
    void acceptModuleQuest(const std::string_view& moduleName);
    bool areModuleQuestsAvailable() const;

    bool isModuleActive(const std::string_view& moduleName) const;
    bool isModuleFinished(const std::string_view& moduleName) const;

    void increaseBodyCount();
    void increaseGenocideCount();
    void increaseTurns();

    unsigned int progress() const;
    unsigned long bodyCount() const;
    unsigned long genocideCount() const;
    unsigned long turns() const;

    void registerModule(const std::string_view& name,
                        const EGameStage neededForStage,
                        std::function<std::string()> questLogFunction = &noQuestLogFunction,
                        std::function<void()> initFunction = &noInitDeInitFunction,
                        std::function<void()> deInitFunction = &noInitDeInitFunction,
                        std::function<void(std::vector<CRoom*>&)> initWorldMapFunction = &noInitWorldMapFunction,
                        std::function<CSupportCompanion*(const std::string_view& name)> supportCompanionsFactory =
                            &noSupportCompanionFactory,
                        std::function<CRoom*(const std::string_view& name)> roomsFactory = &noRoomFactory,
                        std::function<CItem*(const std::string_view& name)> itemsFactory = &noItemFactory,
                        std::function<CTask*(const std::string_view& name)> taskFactory = &noTaskFactory);

    void reRegisterModuleForNextStage(const std::string_view& moduleName);

    virtual nlohmann::json save() const override;

    CSupportCompanion* callModuleSupportCompanionFactory(const std::string_view& name);
    CRoom* callModuleRoomFactory(const std::string_view& name);
    CTask* callModuleTaskFactory(const std::string_view& name);
    CItem* callModuleItemFactory(const std::string_view& name);

private:
    typedef EnumIterator<EGameStage, EGameStage::eNone, EGameStage::eFinale> gameStageIterator;

    struct Module
    {
        std::string moduleName;
        EGameStage gameStage;
        std::function<std::string()> questLogFunction;
        std::function<void()> initFunction;
        std::function<void()> deInitFunction;
        std::function<void(std::vector<CRoom*>&)> initWorldMapFunction;

        std::function<CSupportCompanion*(const std::string_view& name)> supportCompantonFactory;
        std::function<CRoom*(const std::string_view& name)> roomFactory;
        std::function<CItem*(const std::string_view& name)> itemFactory;
        std::function<CTask*(const std::string_view& name)> taskFactory;

        static std::function<bool(const Module)> moduleRegisterNameFilter(const std::string_view& name)
        {
            return [name](const auto module) { return module.moduleName.compare(name) == 0; };
        }
        static std::function<bool(const Module)> moduleRegisterStageFilter(const EGameStage& stage)
        {
            return [stage](auto module) { return module.gameStage == stage; };
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

    struct ModuleQuest
    {
        ModuleQuestInfo questInfo;
        bool accepted = false;
        std::function<void()> questAcceptedFunction;

        static std::function<void()> noQuestAcceptedFunction()
        {
            return []() {};
        }

        static std::function<bool(const ModuleQuest)> moduleQuestNameFilter(const std::string_view& name)
        {
            return [name](const auto quest) { return quest.questInfo.moduleName.compare(name) == 0; };
        }

        static std::function<bool(const ModuleQuest)> moduleQuestAvailableFilter()
        {
            return [](const auto quest) { return quest.accepted == false; };
        }

        static std::function<bool(const ModuleQuest)> moduleQuestAcceptedFilter()
        {
            return [](const auto quest) { return quest.accepted == true; };
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
    void registerModule(const Module& modules);

    EGameStage _currentStage = EGameStage::eNone;
    unsigned long _bodyCount = 0;
    unsigned long _turns = 0;
    unsigned long _genocideCount = 0;

    std::vector<std::string> _finishedModules;
    std::vector<Module> _registeredModules;

    std::vector<ModuleHint> _moduleHints;
    std::vector<ModuleQuest> _moduleQuests;
};
