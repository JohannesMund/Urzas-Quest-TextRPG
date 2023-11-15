#include "moduleressources.h"
#include "cgamemanagement.h"
#include "csewerencounter.h"
#include "ctown.h"
#include "randomizer.h"
#include "ressources.h"

#include <format>

void SewerRessources::initModule()
{
    CGameManagement::getInstance()->registerEncounter(new CSewerEncounter());
}

void SewerRessources::deInitModule()
{
    CGameManagement::getInstance()->unregisterEncounterByModuleName(moduleName());
}

std::string SewerRessources::moduleName()
{
    return "sewer";
}

std::string SewerRessources::encounterName()
{
    return "The Sewer";
}

std::string SewerRessources::getRandomDescription()
{
    return Randomizer::getRandomStringFromVector(
        {"It is wet, it is moldy and the smell is disgusting, you don't even want to think about what' it is you's in "
         "the water you are... oh! was this a Hotdog?",

         "There is a big hole in the wall, and even more stinking, dirty water fills the sewers. You are pretty sure, "
         "that there are things living down here, you did not even know existed.",

         "Funny, what people are throwing away. There is a lotof pretty-ok stuff. But you should not have eaten that "
         "hotdog!",

         "You expected more rats, but this seems more like a the cockroach kind of sewer. At least, you have seen lots "
         "and lots of cockroaches."});
}

std::string SewerRessources::getRandomEnemyName()
{
    return Randomizer::getRandomStringFromVector({"Cockroach",
                                                  "Spider",
                                                  "Rat",
                                                  "Slime",
                                                  std::format("{}red Slime{}", CC::fgRed(), CC::ccReset()),
                                                  std::format("{}green Slime{}", CC::fgLightGreen(), CC::ccReset()),
                                                  std::format("{}blue Slime{}", CC::fgLightBlue(), CC::ccReset())});
}

std::string SewerRessources::getRandomEnemyWeapon()
{
    return Randomizer::getRandomStringFromVector({"spiderweb", "tickeling legs", "teeth", "slime", "slime", "slime"});
}

std::string SewerRessources::getWellDescription(const int i)
{
    switch (i)
    {
    case 1:
    default:
        return "This must be the outlet of the local healer. there is a stream of a red fluid, that looks suspiciously "
               "like a healing potion.";
    case 2:
        return "There is a puddle of suspiciously clear liquid here. it looks magically";
    }
}

std::string SewerRessources::getWellQuestion(const int i)
{
    switch (i)
    {
    case 1:
    default:
        return "do you want to try?";
    case 2:
        return "do you want to drink?";
    }
}

std::string SewerRessources::getWellEffect(const int i)
{
    switch (i)
    {
    case 1:
    default:
        return "Its not really clean, but you are used to a lot. (why on earth did you eath that Hotdog?";
    case 2:
        return "Well, it works.";
    }
}

std::string SewerRessources::getMapRoomDescription()
{
    return "Another pile of rubbish. But this one is different. There are a lot of official looking papers here. "
           "Browsing through them, you find a map of the towns' sewer system.";
}

std::string SewerRessources::getBossRoomDescription()
{
    return std::format("This corner is so different than the rest of the Sewers. Not only is it clean, and not stinky "
                       "here. It is like some kind of... Chapel. It looks totally bizarre, to have such a place in the "
                       "depth of the towns cloaca. Its not that you care all too much about religion, or the specific "
                       "flavour of some god but this is interesting. it seems like this is a shrine for someone callen "
                       "{}. It seems you have just gotten one step closer",
                       Ressources::Game::urza());
}

std::string SewerRessources::getColoredBossString()
{
    return std::format("P{0}apa {1}R{0}oach{1}", CC::fgYellow(), CC::ccReset());
}

std::string SewerRessources::getBossWeapon()
{
    return std::format("L{0}ast {1}R{0}essort{1}", CC::fgYellow(), CC::ccReset());
}

std::string SewerRessources::dungeonEncounterName()
{
    return "SewerDungeon";
}
