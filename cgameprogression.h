#pragma once

#include <functional>
#include <string>
#include <vector>

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

    void progress();
    void reportModuleFinished(const std::string_view& moduleName);

    void increaseBodyCount();

    unsigned int getProgress() const;
    unsigned int getBodyCount() const;

private:
    struct ModuleRegister
    {
        std::string moduleName;
        std::function<void()> initFunction;
        std::function<void()> deInitFunction;
        EGameStage gameStage;

        static std::function<bool(const ModuleRegister&)> moduleRegisterNameFilter(const std::string_view& name)
        {
            return [&name](const auto module) { return module.moduleName.compare(name) == 0; };
        }
        static std::function<bool(const ModuleRegister&)> moduleRegisterStageFilter(const EGameStage& stage)
        {
            return [&stage](auto module) { return module.gameStage == stage; };
        }
    };
    std::vector<ModuleRegister> _moduleRegister;

    CGameProgression();

    bool isModuleFinished(const std::string_view& moduleName);
    void unFinishModule(const std::string_view& moduleName);

    void initModuleByName(const std::string_view& moduleName);
    void deInitModuleByName(const std::string_view& moduleName);

    bool canProgress();

    void deInitStage();
    void initStage();
    void progressToStage(EGameStage stage);

    void reRegisterModule(const std::string_view& name, const EGameStage neededForStage);
    void registerModule(const std::string_view& name,
                        const EGameStage neededForStage,
                        std::function<void()> initFunction,
                        std::function<void()> deInitFunction);

    std::vector<std::string> _finishedModules;

    EGameStage _currentStage = EGameStage::eNone;
    unsigned int _bodyCount = 0;
};
