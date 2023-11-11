#pragma once

#include <string>
#include <vector>

class CGameProgression
{
public:
    enum class EGameStage
    {
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

private:
    bool isModuleFinished(const std::string_view& moduleName);

    bool canProgress();

    void deInitStage();
    void initStage();
    void progressToStage(EGameStage stage);

    std::vector<std::string> _finishedModules;
    EGameStage _currentStage;
    unsigned int _bodyCount = 0;
};
