#include "moduleressources.h"
#include "cgamemanagement.h"
#include "clakeoftearsbosstask.h"
#include "clakeoftearsencounter.h"
#include "clakeoftearstask.h"
#include "colorize.h"
#include "ctask.h"
#include "ressources.h"

#include <format>
#include <string>

Module::ModuleInfo LakeOfTears::moduleInfo()
{
    const auto taskFactory = [](const std::string_view& objectName) -> CTask*
    {
        if (TagNames::LakeOfTears::lakeOfTears.compare(objectName) == 0)
        {
            return new CLakeOfTearsTask();
        }
        if (TagNames::LakeOfTears::lakeOfTearsBoss.compare(objectName) == 0)
        {
            return new CLakeOfTearsBossTask();
        }
        return nullptr;
    };

    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = moduleName();
    moduleInfo.translatorFile = "lakeoftears";
    moduleInfo.gameStage = Module::EGameStage::eProvenAsHero,

    moduleInfo.initFunction = []() { CGameManagement::getInstance()->registerEncounter(new CLakeOfTearsEncounter()); };
    moduleInfo.deInitFunction = []() { CGameManagement::getInstance()->unregisterEncounterByModuleName(moduleName()); };
    moduleInfo.questLogFunction = []() { return "Find and remove the source of the salty water."; };

    moduleInfo.taskFactory = taskFactory;

    return moduleInfo;
}

std::string LakeOfTears::moduleName()
{
    return "LakeOfTears";
}
