#include "moduleressources.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "companions/cguardcompanion.h"
#include "companions/cleilacompanion.h"
#include "ctask.h"
#include "items/cguardstuff.h"
#include "ressources.h"
#include "tasks/cfindguardstask.h"
#include "tasks/cleilarescuecapitaltask.h"

#include <format>
#include <nlohmann/json.hpp>

void LeilaRescue::questAccepted()
{
    CGameManagement::getInstance()->placeTaskOnField(new CFindGuardsTask());
}

std::string LeilaRescue::moduleName()
{
    return "RescueLeilaFromTheDungeon";
}

Module::ModuleInfo LeilaRescue::moduleInfo()
{

    const auto companionFactory = [](const std::string_view& name) -> CSupportCompanion*
    {
        if (TagNames::LeilaRescue::guardCompanion.compare(name) == 0)
        {
            return new CGuardCompanion("");
        }
        if (TagNames::LeilaRescue::leilaCompanion.compare(name) == 0)
        {
            return new CLeilaCompanion();
        }
        return nullptr;
    };

    const auto itemFactory = [](const std::string_view& objectName) -> CItem*
    {
        if (TagNames::LeilaRescue::guardStuff.compare(objectName) == 0)
        {
            return new CGuardStuff();
        }
        return nullptr;
    };

    const auto taskFactory = [](const std::string_view& objectName) -> CTask*
    {
        if (TagNames::LeilaRescue::findGuards.compare(objectName) == 0)
        {
            return new CFindGuardsTask(0);
        }
        if (TagNames::LeilaRescue::leilaRescueCapital.compare(objectName) == 0)
        {
            return new CLeilaRescueCapitalTask();
        }

        return nullptr;
    };

    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = moduleName();
    moduleInfo.translatorFile = "leilarescue";
    moduleInfo.gameStage = Module::EGameStage::eFoundCult;

    moduleInfo.initFunction = []()
    { CGameManagement::getProgressionInstance()->registerModuleQuest(moduleName(), questText(), questAccepted); };
    moduleInfo.questLogFunction = []()
    {
        return std::format("Rescue the beautiful {} from the fangs of her evil father, {}.",
                           Ressources::Game::princessLeila(),
                           Ressources::Game::kingJesster());
    };

    moduleInfo.supportCompantonFactory = companionFactory;
    moduleInfo.taskFactory = taskFactory;
    moduleInfo.itemFactory = itemFactory;

    return moduleInfo;
}

std::string LeilaRescue::questText()
{
    return std::format("Today in the news: {} has been imprisoned! It seems as if she spoke too positive about the "
                       "rebellion, and their latest member (obisously you!), and {} decided, that he has no longer a "
                       "daughter, and threw her into the prison in the dungeons beneath {}. Rumours also tell, the the "
                       "capital guards, who were instructed to protect the princess, have been dismissed and are "
                       "pretty angry towards the king. You might want to find them, to "
                       "get valuable input, on how to get into the capital. This time, it seems that "
                       "she really needs you to come to the rescue!",
                       Ressources::Game::princessLeila(),
                       Ressources::Game::kingJesster(),
                       Ressources::Rooms::getCapital().first);
}
std::string LeilaRescue::getColoredBossString()
{
    return std::format(
        "{0}V{1}enus {2}F{1}ly {0}T{1}rap{3}", CC::fgLightGreen(), CC::fgGreen(), CC::fgRed(), CC::ccReset());
}

std::string LeilaRescue::getBossWeapon()
{
    return std::format("{0}t{1}horny {2}T{1}endrils{3}", CC::fgLightGreen(), CC::fgGreen(), CC::fgRed(), CC::ccReset());
}
