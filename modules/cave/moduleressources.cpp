#include "moduleressources.h"
#include "ccave.h"
#include "colorize.h"
#include "randomizer.h"
#include "roomfactory.h"

#include <format>
#include <vector>

std::string CaveRessources::getRandomDescription()
{
    return Randomizer::getRandomStringFromVector(
        {"A cave, what do you expect? it's dirty, it*s dark, it's stuffy. Not the place to be right now.",

         "A cave, just a cave, but here are huge stalagmites and stalagtites. but which is which? ",

         "It is especially muddy here. It smells musty. There is a mushroom, and it is glowing green. Maybe, if you "
         "are "
         "very hungry. Well, very, very very hungry"});
}

std::string CaveRessources::getRandomEnemyName()
{
    return Randomizer::getRandomStringFromVector({
        "Cave Troll",
        "Spider",
        "Bat",
        "Cave Gnoll",
    });
}

std::string CaveRessources::getRandomEnemyWeapon()
{
    return Randomizer::getRandomStringFromVector(
        {"shabby board with a rusty nail hammered through", "sharp teeth", "sheer muscle power", "a club with spikes"});
}

std::string CaveRessources::getWellDescription(const int i)
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

std::string CaveRessources::getWellQuestion(const int i)
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

std::string CaveRessources::getWellEffect(const int i)
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

std::string CaveRessources::getMapRoomDescription()
{
    return "Next to a wall, you find a dead body. Adventuring is dangerous, you have seen one too many dead people "
           "recently. Nevertheless, this one seemed to have gotten lost. he tried to draw a map in the dirt of a "
           "ground, but, obiously, this did not help him. Nevertheless, the knowledge will help you, not to end up "
           "like this poor guy.";
}

std::string CaveRessources::getBossWeapon()
{
    return "The biggest club you have ever seen";
}

std::string CaveRessources::getColoredBossString()
{
    return std::format("{}The {}Great {}Unclean {}One{}",
                       CC::fgLightGreen(),
                       CC::fgYellow(),
                       CC::fgGreen(),
                       CC::fgLightGreen(),
                       CC::ccReset());
}

std::string CaveRessources::moduleName()
{
    return "Cave";
}

void CaveRessources::initModule()
{
}

void CaveRessources::deInitModule()
{
}

void CaveRessources::initWorldMap(std::vector<CRoom*>& rooms)
{
    rooms.push_back(new CCave());
}

std::string CaveRessources::questLog()
{
    return std::format("Clear the {0}Cave{2} and defeat the evil {0}cave boss{2}.",
                       CC::fgDarkGray(),
                       CC::fgLightGreen(),
                       CC::ccReset());
}
