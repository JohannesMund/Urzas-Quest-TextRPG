#include "moduleressources.h"
#include "ccave.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "copencaveencounter.h"
#include "copencavetask.h"
#include "randomizer.h"
#include "roomfactory.h"

#include <format>
#include <vector>

std::string Cave::getRandomDescription()
{
    return Randomizer::getRandomStringFromVector(
        {"A cave, what do you expect? it's dirty, it*s dark, it's stuffy. Not the place to be right now.",

         "A cave, just a cave, but here are huge stalagmites and stalagtites. but which is which? ",

         "It is especially muddy here. It smells musty. There is a mushroom, and it is glowing green. Maybe, if you "
         "are "
         "very hungry. Well, very, very very hungry"});
}

std::string Cave::getRandomEnemyName()
{
    return Randomizer::getRandomStringFromVector({
        "Cave Troll",
        "Spider",
        "Bat",
        "Cave Gnoll",
    });
}

std::string Cave::getRandomEnemyWeapon()
{
    return Randomizer::getRandomStringFromVector(
        {"shabby board with a rusty nail hammered through", "sharp teeth", "sheer muscle power", "a club with spikes"});
}

std::string Cave::getWellDescription(const int i)
{
    switch (i)
    {
    case 1:
    default:
        return "This room is different. All of a sudden, it does no longer smell like mold and mud. A tiny stream, of "
               "increadibly blue water, running out of a small hole in"
               " the wall.";
    case 2:
        return "On first glance, this is a room like the others, but in one corner, you spot funny looking mushrooms";
    case 3:
        return "Here you can see an espacially huge stalagtite. The water from this stalagtite is collected in a small "
               "puddle. The puddle looks extremely clean.";
    }
}

std::string Cave::getWellQuestion(const int i)
{
    switch (i)
    {
    case 1:
    default:
        return "Do you want to drink from the stream?";
    case 2:
        return "This is probably a big mistake, but do you want to eat from the mushrooms?";
    case 3:
        return "The water looks refreshing. You should have a drink.";
    }
}

std::string Cave::getWellEffect(const int i)
{
    switch (i)
    {
    case 1:
    default:
        return "The water is clean and tastes great! You feel much better now.";
    case 2:
        return "The mushrooms don't taste very good. But there are no funny effects. You just feel... healed.";
    case 3:
        return "The water is cold and refreshing. You feel great!";
    }
}

std::string Cave::getMapRoomDescription()
{
    return "Next to a wall, you find a dead body. Adventuring is dangerous, you have seen one too many dead people "
           "recently. Nevertheless, this one seemed to have gotten lost. he tried to draw a map in the dirt of a "
           "ground, but, obiously, this did not help him. Nevertheless, the knowledge will help you, not to end up "
           "like this poor guy.";
}

std::string Cave::getBossWeapon()
{
    return "The biggest club you have ever seen";
}

std::string Cave::getColoredBossString()
{
    return std::format("{}The {}Great {}Unclean {}One{}",
                       CC::fgLightGreen(),
                       CC::fgYellow(),
                       CC::fgGreen(),
                       CC::fgLightGreen(),
                       CC::ccReset());
}

Module::ModuleInfo Cave::moduleInfo()
{
    const auto roomFactory = [](const std::string_view& objectName) -> CRoom*
    {
        if (TagNames::Cave::cave.compare(objectName) == 0)
        {
            return new CCave();
        }
        return nullptr;
    };

    const auto taskFactory = [](const std::string_view& objectName) -> CTask*
    {
        if (TagNames::Cave::openCave.compare(objectName) == 0)
        {
            return new COpenCaveTask();
        }
        return nullptr;
    };

    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = moduleName();
    moduleInfo.translatorFile = "cave";
    moduleInfo.gameStage = Module::EGameStage::eProvenAsHero,

    moduleInfo.initFunction = []() { CGameManagement::getInstance()->registerEncounter(new COpenCaveEncounter()); };
    moduleInfo.deInitFunction = []() { CGameManagement::getInstance()->unregisterEncounterByModuleName(moduleName()); };
    moduleInfo.questLogFunction = []()
    {
        return std::format("Clear the {0}Cave{2} and defeat the evil {0}cave boss{2}.",
                           CC::fgDarkGray(),
                           CC::fgLightGreen(),
                           CC::ccReset());
    };

    moduleInfo.taskFactory = taskFactory;
    moduleInfo.roomFactory = roomFactory;
    moduleInfo.initWorldMapFunction = [](std::vector<CRoom*>& rooms) { rooms.push_back(new CCave()); };

    return moduleInfo;
}

std::string Cave::moduleName()
{
    return "Cave";
}

std::string Cave::dungeonEncounterName()
{
    return moduleName() + "Dungeon";
}
