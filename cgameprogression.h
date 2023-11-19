#pragma once

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

    void initEncounters();

    EGameStage currentGameStage() const;

    std::vector<std::string> getQuestLog() const;

    void progress();
    void reportModuleFinished(const std::string_view& moduleName);

    bool isModuleActive(const std::string_view& moduleName) const;
    bool isModuleFinished(const std::string_view& moduleName) const;

    void initWorldMap(std::vector<CRoom*>& rooms) const;

    void increaseBodyCount();

    unsigned int getProgress() const;
    unsigned int getBodyCount() const;

private:
    struct ModuleRegister
    {
        std::string moduleName;
        EGameStage gameStage;
        std::function<std::string()> questLogFunction;
        std::function<void()> initFunction;
        std::function<void()> deInitFunction;
        std::function<void(std::vector<CRoom*>&)> initWorldMapFunction;

        static std::function<bool(const ModuleRegister&)> moduleRegisterNameFilter(const std::string_view& name)
        {
            return [&name](const auto module) { return module.moduleName.compare(name) == 0; };
        }
        static std::function<bool(const ModuleRegister&)> moduleRegisterStageFilter(const EGameStage& stage)
        {
            return [&stage](auto module) { return module.gameStage == stage; };
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
    std::vector<ModuleRegister> _moduleRegister;

    CGameProgression();

    void unFinishModule(const std::string_view& moduleName);

    void initModuleByName(const std::string_view& moduleName);
    void deInitModuleByName(const std::string_view& moduleName);

    bool canProgress();

    void deInitStage();
    void initStage();
    void progressToStage(EGameStage stage);

    void reRegisterModule(const std::string_view& name, const EGameStage neededForStage);
    void registerModule(
        const std::string_view& name,
        const EGameStage neededForStage,
        std::function<std::string()> questLogFunction = &ModuleRegister::noQuestLogFunction,
        std::function<void()> initFunction = &ModuleRegister::noInitDeInitFunction,
        std::function<void()> deInitFunction = &ModuleRegister::noInitDeInitFunction,
        std::function<void(std::vector<CRoom*>&)> initWorldMapFunction = &ModuleRegister::noInitWorldMapFunction);

    std::vector<std::string> _finishedModules;

    EGameStage _currentStage = EGameStage::eNone;
    unsigned int _bodyCount = 0;
};
