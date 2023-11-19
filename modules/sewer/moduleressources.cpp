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
        {std::format("It is wet, it is moldy and the smell is disgusting, you don't even want to think about what' it "
                     "is you's in "
                     "the water you are... oh! was this a {}?",
                     hotdog()),

         "There is a big hole in the wall, and even more stinking, dirty water fills the sewers. You are pretty sure, "
         "that there are things living down here, you did not even know existed.",

         std::format("Funny, what people are throwing away. There is a lotof pretty-ok stuff. But you should not have "
                     "eaten that "
                     "{}!",
                     hotdog()),

         "You expected more rats, but this seems more like a the cockroach kind of sewer. At least, you have seen lots "
         "and lots of cockroaches.",

         "There is suspiciously much slime here. it comes out of pipes, drops from the walls and the ceiling. Some of "
         "it seems to be acidic. You wonder, when it will attack you."});
}

std::string SewerRessources::getRandomEnemyName()
{
    return Randomizer::getRandomStringFromVector({"Cockroach",
                                                  "Spider",
                                                  "Rat",
                                                  "Slime",
                                                  std::format("{}yellow Slime{}", CC::fgLightYellow(), CC::ccReset()),
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
        return std::format("There is a puddle of suspiciously clear liquid here. it looks magically. You could use "
                           "something to make you feel better. (Oh, that {}!)",
                           hotdog());
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
        return std::format("Its not really clean, but you are used to a lot. (why on earth did you eath that {}?",
                           hotdog());
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

std::string SewerRessources::hotdog()
{
    return std::format("{0}H{1}o{2}t{0}dog{3}", CC::fgYellow(), CC::fgLightRed(), CC::fgLightYellow(), CC::ccReset());
}

std::string SewerRessources::questLog()
{
    return "Rescue the missing children from the cities sewers.";
}
