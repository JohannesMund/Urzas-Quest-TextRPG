#pragma once

#include <functional>
#include <string>
#include <vector>

class CGameProgression
{
public:
    enum class EGameStage
    {
        eNone,
        eStart,
        eSeenBard,
        eProvenAsHero,
        eLearnedAboutCult
    };

    void initEncounters();

    CGameProgression();

    EGameStage currentGameStage() const;

    void progress();
    void reportModuleFinished(const std::string_view& moduleName);

    void increaseBodyCount();

    unsigned int getProgress() const;
    unsigned int getBodyCount() const;

private:
    bool isModuleFinished(const std::string_view& moduleName);
    void unFinishModule(const std::string_view& moduleName);

    void initModuleByName(const std::string_view& moduleName);
    void deInitModuleByName(const std::string_view& moduleName);

    bool canProgress();

    void deInitStage();
    void initStage();
    void progressToStage(EGameStage stage);

    void reRegisterModule(const std::string_view& name, const EGameStage neededForStage);
    void registerModule(const std::string_view& name, const EGameStage neededForStage);

    std::vector<std::pair<std::string, EGameStage>> _modulesForStage;

    static std::function<bool(const std::pair<std::string, EGameStage>&)> modPairNameFilter(
        const std::string_view& name);

    static std::function<bool(const std::pair<std::string, EGameStage>&)> modPairStageFilter(const EGameStage& stage);

    std::vector<std::string> _finishedModules;

    EGameStage _currentStage = EGameStage::eNone;
    unsigned int _bodyCount = 0;
};
