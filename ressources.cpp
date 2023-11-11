#include "ressources.h"
#include "colorconsole.h"
#include "randomizer.h"

#include "bard/moduleressources.h"

#include <algorithm>
#include <format>
#include <map>

std::string Ressources::Rooms::getRandomDescription()
{
    std::vector<std::string> _roomDescriptions = {
        "A Meadow. With grass. A lot of grass. It is green. Did i mention the grass? Oh, there is a sheep. Do you like "
        "sheep? I like sheep. There is one.",

        "A deep, dark Forest. Trees and Bushes around you. The ground is muddy and wet. Was that a fairy? Maybe a "
        "forest "
        "fairy? In this case, her name is probably \"Holla\".",

        "The shore of a lake. This is one big lake, so big, that it should be called \"Lake Enormous\". But it is just "
        "a "
        "lake. On second glance, not even a big one."};
    return _roomDescriptions.at(Randomizer::getRandom(_roomDescriptions.size()));
}

std::pair<std::string, std::string> Ressources::Items::getRandomJunkItems()
{
    std::vector<std::pair<std::string, std::string>> items = {
        {{std::format("{}Stick{}", CC::fgYellow(), CC::ccReset())},
         {"A stick, just a stick. Maybe magical? There is no label stating \"Godly Magic Stick of the "
          "Whale\". On the "
          "other hand, there no label stating, that this stick is not a \"Godly Magic Stick of the Whale\"."}},
        {{sock()},
         {"A single sock. A single dirty sock. Useless without the other one. Who on earth throws away a "
          "single Sock??"}},
        {{otherSock()},
         {"There it is, the other sock. A single dirty sock. Now you have both but who on earth throws away two single "
          "Socks seperately??"}},
        {{std::format("{}Rock{}", CC::fgCyan(), CC::ccReset())},
         {"This is a good rock, so good, that it might be used in an epic \"Rock Paper Sicsors\" battle."}},
        {{std::format("{}Boot{}", CC::fgYellow(), CC::ccReset())},
         {"An old, single boot made from leather.Good, expensive leather. But is damaged and dirty. And it is just "
          "a single boot."}},
        {{"Vase"},
         {"This is one beautiful vase. It will look nice on your table. or on a sideboard. you could fill it with "
          "flowers. Or you just throw it away, for somone else to find ist."}}};

    return items.at(Randomizer::getRandom(items.size()));
}

unsigned int Ressources::Config::getXpForLevel(const unsigned int level)
{
    static const std::vector<int> xpForLevel = {0, 300, 700, 1300, 2000, 4000, 8000, 14000, 20000};
    if (level < xpForLevel.size())
    {
        return xpForLevel.at(level);
    }
    return xpForLevel.at(xpForLevel.size() - 1);
}

std::string Ressources::Enemies::getRandomEnemyName()
{
    std::vector<std::string> names = {"Bob, the Cowboy",
                                      "Eddie, the Cowboy",
                                      "Angry Rat",
                                      "Stinky Bat",
                                      "Greedy Vulture",
                                      "Huge Barbarian",
                                      "Pussy, the Octopus",
                                      "Tentacool",
                                      "Tentacruel",
                                      "Kang",
                                      "Kodos"};
    return names.at(Randomizer::getRandom(names.size()));
}

std::string Ressources::Enemies::getRandomEnemyWeapon()
{
    std::vector<std::string> weapons = {"shabby board with a rusty nail hammered through",
                                        "sharp teeth",
                                        "sheer muscle power",
                                        "a club with spikes",
                                        "a Nokia 3210",
                                        "tantacles",
                                        "laser gun"};
    return weapons.at(Randomizer::getRandom(weapons.size()));
}

std::pair<std::string, std::string> Ressources::Rooms::getRandomTown()
{
    std::vector<std::pair<std::string, std::string>> towns = {
        {"Hafnarfjodur", "The City of Elves. Built high in the treetops of ancient Trees"},
        {"Peridotspring", "Deep Caves, carved in huge mountains built this citiy of the dwarfs"},
        {"Wallachia", "An Oasis surrounded by a huge desert."},
        {"Bruchtal", "City of man, capital of the land."},
        {"Mudpool", "The Home of the trolls. Everything is dirty and stinky here."},
        {"Timbuktu",
         "The mysterous city, where the pepper grows. Many legendary heroes have been sent here. But on second sight, "
         "it is just a city."}};
    return towns.at(Randomizer::getRandom(towns.size()));
}

std::string Ressources::Companion::nameForCompanionType(const ECompanionType& tp, const unsigned int level)
{
    std::map<ECompanionType, std::vector<std::string>> companions = {
        {ECompanionType::eHealer, {"Chick", "Sparrow", "Parrot", "Griffon", "Phoenix"}},
        {ECompanionType::eDefender, {"Whelp", "Dog", "Wolf", "Ice wolf", "Cerberus"}},
        {ECompanionType::eAttacker, {"Kitten", "Cat", "Lynx", "Tiger", "Sphinx"}},
        {ECompanionType::eScaryMonster,
         {"Baby Dragon", "Young Dragon", "Adult Dragon", "Old Dragon", "Ancient Hellfire Dragon"}}};

    return companions.at(tp).at(std::min(companionLevelCap, std::max(level, 1U)) - 1);
}

Ressources::Companion::ECompanionType Ressources::Companion::getRandomCompanionType()
{
    std::vector<ECompanionType> v;
    v.push_back(ECompanionType::eAttacker);
    v.push_back(ECompanionType::eAttacker);
    v.push_back(ECompanionType::eAttacker);
    v.push_back(ECompanionType::eAttacker);
    v.push_back(ECompanionType::eAttacker);

    v.push_back(ECompanionType::eDefender);
    v.push_back(ECompanionType::eDefender);
    v.push_back(ECompanionType::eDefender);
    v.push_back(ECompanionType::eDefender);
    v.push_back(ECompanionType::eDefender);

    v.push_back(ECompanionType::eHealer);
    v.push_back(ECompanionType::eHealer);
    v.push_back(ECompanionType::eHealer);

    v.push_back(ECompanionType::eScaryMonster);

    std::shuffle(v.begin(), v.end(), std::default_random_engine(Randomizer::getRandomEngineSeed()));
    return v.at(0);
}

std::string Ressources::Companion::typeAsString(const ECompanionType& tp)
{
    switch (tp)
    {
    case ECompanionType::eAttacker:
        return "fighter";
        break;
    case ECompanionType::eDefender:
        return "protector";
        break;
    case ECompanionType::eHealer:
        return "healer";
        break;
    case ECompanionType::eScaryMonster:
        return "scary monster";
        break;
    }
    return "";
}

std::pair<std::string, std::string> Ressources::Enemies::getRandomBountyName()
{
    std::vector<std::pair<std::string, std::string>> names = {
        {"Fat Eddie", "Blackmailing the Mayor"},
        {"Robo Devil", "Stealing people's hands"},
        {"Evil Wizard", "Doing evil wizard things"},
        {"Robin Would", "Stealing from the rich"},
        {"Taffy, the Pirate", "Crimes against the world government"}};
    return names.at(Randomizer::getRandom(names.size()));
}

std::string Ressources::Rooms::getRandomRumor()
{
    std::vector<std::string> rumors = {"The king has stupid ears.",
                                       "There is a huge treasure hidden beneath the mountain.",
                                       "The mayor of this town has an affair with a donkey."};
    return rumors.at(Randomizer::getRandom(rumors.size()));
}

std::string Ressources::whoTheFuckIsUrza()
{
    return std::format("{}wh{}o t{}he f{}uck {}is {}?{}",
                       CC::fgLightYellow(),
                       CC::fgYellow(),
                       CC::fgLightGreen(),
                       CC::fgLightYellow(),
                       CC::fgGreen(),
                       urza(),
                       CC::ccReset());
}

std::string Ressources::urza()
{
    return std::format("{}Ur{}za{}", CC::fgLightGreen(), CC::fgYellow(), CC::ccReset());
}

std::string Ressources::urzaWhoTheFuckIsUrza()
{
    return std::format("{}{}", urza(), whoTheFuckIsUrza());
}

std::string Ressources::Items::sock()
{
    return std::format("{}S{}o{}c{}k{}", CC::fgRed(), CC::fgYellow(), CC::fgRed(), CC::fgYellow(), CC::ccReset());
}
std::string Ressources::Items::otherSock()
{
    return std::format("{}The other {}S{}o{}c{}k{}",
                       CC::fgRed(),
                       CC::fgYellow(),
                       CC::fgRed(),
                       CC::fgYellow(),
                       CC::fgRed(),
                       CC::ccReset());
}
