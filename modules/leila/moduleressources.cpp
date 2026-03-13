#include "moduleressources.h"
#include "cgamemanagement.h"
#include "cleilaencounter.h"
#include "colorize.h"
#include "ctask.h"
#include "ressources.h"
#include "tasks/cleilatask.h"
#include "tasks/cleilatowntask.h"
#include "tasks/ctattooparlor.h"

#include <format>

namespace
{
template <typename... Args>
std::string tr(const std::string_view& textId, Args&&... formatArgs)
{
    return CTranslator::tr(Leila::moduleName(), TagNames::Translator::ressources, textId, formatArgs...);
}
} // namespace

Module::ModuleInfo Leila::moduleInfo()
{
    const auto taskFactory = [](const std::string_view& objectName) -> CTask*
    {
        if (TagNames::Leila::leila.compare(objectName) == 0)
        {
            return new CLeilaTask();
        }
        if (TagNames::Leila::leilaTown.compare(objectName) == 0)
        {
            return new CLeilaTownTask();
        }
        if (TagNames::Leila::tatooParlor.compare(objectName) == 0)
        {
            return new CTattooParlor();
        }
        return nullptr;
    };

    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = moduleName();
    moduleInfo.translatorFile = "leila";
    moduleInfo.gameStage = Module::EGameStage::eSeenBard,

    moduleInfo.initFunction = []() { CGameManagement::getInstance()->registerEncounter(new CLeilaEncounter()); };
    moduleInfo.deInitFunction = []() { CGameManagement::getInstance()->unregisterEncounterByModuleName(moduleName()); };
    moduleInfo.questLogFunction = []()
    { return std::format("Rescue the beautiful {}.", Ressources::Game::princessLeila()); };

    moduleInfo.taskFactory = taskFactory;

    return moduleInfo;
}

std::string Leila::inky()
{
    return tr("{}I{}nky{}", CC::fgWhite(), CC::fgBlack(), CC::ccReset());
}

std::string Leila::inkystattooParlor()
{
    return tr("{}s Wandering tattoo parlor", inky());
}

std::string Leila::moduleName()
{
    return "RescuePrincessLayla";
}
