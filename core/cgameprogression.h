#pragma once

#include "enumiterator.h"
#include "modulesregister.h"
#include "ressources.h"

#include <functional>
#include <string>
#include <vector>

class CRoom;
class CGameProgression
{
    friend class CGameManagement;

public:
    Ressources::Game::EGameStage currentGameStage() const;
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
    typedef EnumIterator<Ressources::Game::EGameStage,
                         Ressources::Game::EGameStage::eNone,
                         Ressources::Game::EGameStage::eFinale>
        gameStageIterator;

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

    void progressToStage(Ressources::Game::EGameStage stage);

    void reRegisterModule(const std::string_view& name, const Ressources::Game::EGameStage neededForStage);

    void registerModule(const ModuleRegister::Module& modules);

    Ressources::Game::EGameStage _currentStage = Ressources::Game::EGameStage::eNone;
    unsigned long _bodyCount = 0;
    unsigned long _turns = 0;

    std::vector<std::string> _finishedModules;
    std::vector<ModuleRegister::Module> _moduleRegister;
    std::vector<ModuleHint> _moduleHints;
};
