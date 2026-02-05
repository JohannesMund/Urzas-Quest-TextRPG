#pragma once

#include "save/savetagnames.h"

#include <functional>
#include <string>
#include <vector>

class CRoom;
class CSupportCompanion;
class CItem;
class CTask;

namespace Module
{

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

static inline void noInitDeInitFunction()
{
}
static inline void noInitWorldMapFunction(std::vector<CRoom*>&)
{
}
static inline CSupportCompanion* noSupportCompanionFactory(const std::string_view&)
{
    return nullptr;
}
static inline CRoom* noRoomFactory(const std::string_view&)
{
    return nullptr;
}
static inline CItem* noItemFactory(const std::string_view&)
{
    return nullptr;
}
static inline CTask* noTaskFactory(const std::string_view&)
{
    return nullptr;
}

static inline std::string noQuestLogFunction()
{
    return std::string{};
}

struct ModuleInfo
{
    ModuleInfo()
    {
        moduleName = "";
        translatorFile = "";
        gameStage = EGameStage::eNone;

        questLogFunction = &noQuestLogFunction;
        initFunction = &noInitDeInitFunction;
        deInitFunction = &noInitDeInitFunction;
        initWorldMapFunction = &noInitWorldMapFunction;

        supportCompantonFactory = &noSupportCompanionFactory;
        roomFactory = &noRoomFactory;
        itemFactory = &noItemFactory;
        taskFactory = &noTaskFactory;
    }

    std::string moduleName;
    std::string translatorFile;
    EGameStage gameStage;
    std::function<std::string()> questLogFunction;
    std::function<void()> initFunction;
    std::function<void()> deInitFunction;
    std::function<void(std::vector<CRoom*>&)> initWorldMapFunction;

    std::function<CSupportCompanion*(const std::string_view& name)> supportCompantonFactory;
    std::function<CRoom*(const std::string_view& name)> roomFactory;
    std::function<CItem*(const std::string_view& name)> itemFactory;
    std::function<CTask*(const std::string_view& name)> taskFactory;

    static std::function<bool(const ModuleInfo)> moduleRegisterNameFilter(const std::string_view& name)
    {
        return [name](const auto module) { return module.moduleName.compare(name) == 0; };
    }
    static std::function<bool(const ModuleInfo)> moduleRegisterStageFilter(const EGameStage& stage)
    {
        return [stage](auto module) { return module.gameStage == stage; };
    }
};

} // namespace Module