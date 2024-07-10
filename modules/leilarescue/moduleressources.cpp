#include "moduleressources.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "ressources.h"
#include "tasks/cfindguardstask.h"

#include <format>

void LeilaRescueRessources::initModule()
{
    CGameManagement::getProgressionInstance()->registerModuleQuest(moduleName(), questText(), questAccepted);
}

void LeilaRescueRessources::deInitModule()
{
}

void LeilaRescueRessources::questAccepted()
{
    CGameManagement::getInstance()->placeTaskOnField(new CFindGuardsTask());
}

std::string LeilaRescueRessources::moduleName()
{
    return "RescueLeilaFromTheDungeon";
}

std::string LeilaRescueRessources::questLog()
{
    return std::format("Rescue the beautiful {} from the fangs of her evil father, {}.",
                       Ressources::Game::princessLeila(),
                       Ressources::Game::kingJesster());
}

std::string LeilaRescueRessources::questText()
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

std::string LeilaRescueRessources::getColoredBossString()
{
    return std::format(
        "{0}V{1}enus {2}F{1}ly {0}T{1}rap{3}", CC::fgLightGreen(), CC::fgGreen(), CC::fgRed(), CC::ccReset());
}

std::string LeilaRescueRessources::getBossWeapon()
{
    return std::format("{0}t{1}horny {2}T{1}endrils{3}", CC::fgLightGreen(), CC::fgGreen(), CC::fgRed(), CC::ccReset());
}
