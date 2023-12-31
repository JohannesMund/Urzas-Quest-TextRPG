#include "ressources.h"
#include "colorize.h"
#include "randomizer.h"

#include <algorithm>
#include <format>
#include <map>

std::string Ressources::Rooms::getRandomDescription()
{
    return Randomizer::getRandomStringFromVector(
        {"A Meadow. With grass. A lot of grass. It is green. Did i mention the grass? Oh, there is a sheep. Do you "
         "like "
         "sheep? I like sheep. There is one.",

         "A deep, dark Forest. Trees and Bushes around you. The ground is muddy and wet. Was that a fairy? Maybe a "
         "forest "
         "fairy? In this case, her name is probably \"Holla\".",

         "The shore of a lake. This is one big lake, so big, that it should be called \"Lake Enormous\". But it is "
         "just "
         "a "
         "lake. On second glance, not even a big one."});
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
        {{std::format("V{0}a{1}s{0}e{1}", CC::fgBlue(), CC::ccReset())},
         {"This is one beautiful vase. It will look nice on your table. or on a sideboard. you could fill it with "
          "flowers. Or you just throw it away, for somone else to find ist."}},
        {{"Flask"},
         {"An empty flask. Like the ones filled with magic potions, only without the potion. This one is filled with "
          "nothing."}},
        {{std::format("{0}Col{1}l{2}ec{0}tio{1}n o{0}f l{3}eav{1}es{4}",
                      CC::fgYellow(),
                      CC::fgLightYellow(),
                      CC::fgLightGreen(),
                      CC::fgLightRed(),
                      CC::ccReset())},
         {"A collection of especially beautiful leaves."}},
        {{std::format("{}Ring{}", CC::fgYellow(), CC::ccReset())},
         {std::format("A ring, probably from a bubblegum machine (What is a bubble gum machine?), anyway, nothing for "
                      "proposing to {}.",
                      Game::princessLayla())}}};

    return items.at(Randomizer::getRandom((unsigned int)items.size()));
}

std::string Ressources::Enemies::getRandomEnemyName()
{
    return Randomizer::getRandomStringFromVector({"Bob, the Cowboy",
                                                  "Eddie, the Cowboy",
                                                  "Angry Rat",
                                                  "Stinky Bat",
                                                  "Greedy Vulture",
                                                  "Huge Barbarian",
                                                  "Pussy, the Octopus",
                                                  "Tentacool",
                                                  "Tentacruel",
                                                  "Kang",
                                                  "Kodos"});
}

std::string Ressources::Enemies::getRandomEnemyWeapon()
{
    return Randomizer::getRandomStringFromVector({"shabby board with a rusty nail hammered through",
                                                  "sharp teeth",
                                                  "sheer muscle power",
                                                  "a club with spikes",
                                                  "a Nokia 3210",
                                                  "tantacles",
                                                  "laser gun"});
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
    return towns.at((unsigned int)Randomizer::getRandom(towns.size()));
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
    return names.at((unsigned int)Randomizer::getRandom(names.size()));
}

std::string Ressources::Rooms::getRandomRumor()
{
    return Randomizer::getRandomStringFromVector({"The king has stupid ears.",
                                                  "There is a huge treasure hidden beneath the mountain.",
                                                  "The mayor of this town has an affair with a donkey."});
}

std::string Ressources::Game::whoTheFuckIsUrza()
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

std::string Ressources::Game::urza()
{
    return std::format("{}Ur{}za{}", CC::fgLightGreen(), CC::fgYellow(), CC::ccReset());
}

std::string Ressources::Game::urzaWhoTheFuckIsUrza()
{
    return std::format("{} {}", urza(), whoTheFuckIsUrza());
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

namespace
{

void colorizeNames(std::vector<std::string>& names, std::string cc1, std::string cc2)
{
    for (auto& n : names)
    {
        n = CC::colorizeString(n, cc1, cc2);
    }
}

std::pair<std::vector<std::string>, std::string> getRandomSwordNamesAndDescription(
    const Ressources::Items::EQuality quality)
{
    std::vector<std::string> names;
    std::string description;

    switch (quality)
    {
    case Ressources::Items::EQuality::eJunk:
    default:
        names = {"Stick, shaped like a sword", "Sword, shaped like a stick", "Stick-Sword"};
        colorizeNames(names, CC::fgGreen(), CC::fgYellow());
        description = "A stick, shaped like a sword. Or a sword, shaped like a stick? It is a sword-stick";
        break;
    case Ressources::Items::EQuality::eFair:
    {
        switch (Randomizer::getRandom(3))
        {
        case 0:
        default:
            names = {"Trunk", "Club", "Big Club", "Metal-plated Club"};
            colorizeNames(names, CC::fgYellow(), CC::fgLightYellow());
            description = "A big trunk, used as club. Clubby cluby ouchie ouchie";
            break;
        case 1:
            names = {"Steak Knife", "Dagger", "Polished Dagger", "Pointy Dagger"};
            colorizeNames(names, CC::fgLightBlue(), CC::fgLightCyan());
            description = "A good steak knife. Usable as a dagger.";
            break;
        case 2:
            names = {"Fighting Stick", "Fighting Staff", "Enhanced Fighting Staff", "Battle staff"};
            colorizeNames(names, CC::fgLightYellow(), CC::fgYellow());
            description = "A Stick, usable for fighting";
            break;
        }
        break;
    }
    case Ressources::Items::EQuality::eGood:
    {
        switch (Randomizer::getRandom(5))
        {
        case 0:
        default:
            names = {"Sword", "Sword +1", "Sword +2", "Sword +3", "Sword +4"};
            colorizeNames(names, CC::fgRed(), CC::fgYellow());
            description = "This is one good sword. Made for a glorious knight";
            break;
        case 1:
            names = {"Mace", "Mace +1", "Mace +2", "Mace +3", "Mace +4"};
            colorizeNames(names, CC::fgBlue(), CC::fgLightBlue());
            description = "A Mace, like the onse used by the battle clerics of the king.";
            break;
        case 2:
            names = {"Halberd", "Halberd +1", "Halberd +2", "Halberd +3", "Halberd +4"};
            colorizeNames(names, CC::fgLightRed(), CC::fgLightGray());
            description = "A large Halberd, made for the Kings guards";
            break;
        case 3:
            names = {"Dagger", "Dagger +1", "Dagger +2", "Dagger +3", "Dagger +4"};
            colorizeNames(names, CC::fgLightGray(), CC::fgDarkGray());
            description = "An awesomne, hand-crafted Dagger, fast and deadly";
            break;
        case 4:
            names = {"Whip", "Whip +1", "Whip +2", "Whip +3", "Whip +4"};
            colorizeNames(names, CC::fgLightMagenta(), CC::fgRed());
            description = "Who fights with a whip? Everybody should, considering the reach of this beast";
            break;
        }
        break;
    }
    case Ressources::Items::EQuality::eAwesomne:
    {
        switch (Randomizer::getRandom(5))
        {
        case 0:
        default:
            names = {"godly Stick of the Whale",
                     "godly Stick of the Whale +1",
                     "godly Stick of the Whale +2",
                     "godly Stick of the Whale +3",
                     "godly Stick of the Whale +4",
                     "godly Stick of the Whale +5",
                     "godly Stick of the Whale +6",
                     "godly Stick of the Whale +7",
                     "godly Stick of the Whale +8"};
            colorizeNames(names, CC::fgBlue(), CC::fgLightBlue());
            description = "Its a stick, but other than the other sticks, it has a label \"godly Stick of the Whale\"";
            break;
        case 1:
            names = {"antique Sword of the Ancients",
                     "antique Sword of the Ancients +1",
                     "antique Sword of the Ancients +2",
                     "antique Sword of the Ancients +3",
                     "antique Sword of the Ancients +4",
                     "antique Sword of the Ancients +5",
                     "antique Sword of the Ancients +6",
                     "antique Sword of the Ancients +7",
                     "antique Sword of the Ancients +8"};
            colorizeNames(names, CC::fgYellow(), CC::fgLightYellow());
            description = "This is one really really old and magic sword.";
            break;
        case 2:
            names = {
                "Trident of the Demon king",
                "Trident of the Demon king +1",
                "Trident of the Demon king +2",
                "Trident of the Demon king +3",
                "Trident of the Demon king +4",
                "Trident of the Demon king +5",
                "Trident of the Demon king +6",
                "Trident of the Demon king +7",
                "Trident of the Demon king +8",
            };
            colorizeNames(names, CC::fgRed(), CC::fgDarkGray());
            description =
                std::format("A cool trident, the spikes seem to glow, and they are hot! well, not as hot as {}.",
                            Ressources::Game::layla());
            break;
        case 3:
            names = {"Whip of the beast tamer",
                     "Whip of the beast tamer +1",
                     "Whip of the beast tamer +2",
                     "Whip of the beast tamer +3",
                     "Whip of the beast tamer +4",
                     "Whip of the beast tamer +5",
                     "Whip of the beast tamer +6",
                     "Whip of the beast tamer +7",
                     "Whip of the beast tamer +8"};
            colorizeNames(names, CC::fgLightGray(), CC::fgYellow());
            description = "This whip has certainly tamed many beasts. Who knows, maybe it works on a certain princess?";
            break;
        case 4:
            names = {"Holy mace of the Nephalim",
                     "Holy mace of the Nephalim +1",
                     "Holy mace of the Nephalim +2",
                     "Holy mace of the Nephalim +3",
                     "Holy mace of the Nephalim +4",
                     "Holy mace of the Nephalim +5",
                     "Holy mace of the Nephalim +6",
                     "Holy mace of the Nephalim +7",
                     "Holy mace of the Nephalim +8"};
            colorizeNames(names, CC::fgLightYellow(), CC::fgLightGray());
            description = "A mace, so holy, you can stick a tail on it, and call it a beaver.";
            break;
        }
        break;
    }
    }

    return std::make_pair(names, description);
}

std::pair<std::vector<std::string>, std::string> getRandomShieldNamesAndDescription(
    const Ressources::Items::EQuality quality)
{
    std::vector<std::string> names;
    std::string description;

    switch (quality)
    {
    case Ressources::Items::EQuality::eJunk:
    default:
        names = {"wheathered wooden board", "wooden board", "robust wooden board"};
        colorizeNames(names, CC::fgYellow(), CC::fgLightRed());
        description = "A wooden board. It can protect you from... well, not much but it offers a little protection.";
        break;
    case Ressources::Items::EQuality::eFair:
    {
        switch (Randomizer::getRandom(3))
        {
        case 0:
        default:
            names = {"Damaged Buckler", "Repaired Buckler", "Buckler", "Shiny Buckler"};
            colorizeNames(names, CC::fgYellow(), CC::fgCyan());
            description = "A Buckler, a small, round, savage shield.";
            break;
        case 1:
            names = {"Ripped Leather Shield", "Repaired Leather Shield", "Leather Shield", "Shiny Leather Shield"};
            colorizeNames(names, CC::fgRed(), CC::fgYellow());
            description = "A shield made of leather, light and sturdy.";
            break;
        case 2:
            names = {"Brittle Wooden Shield", "Repaired Wooden Shield", "Wooden Shield", "Shiny Wooden Shield"};
            colorizeNames(names, CC::fgLightGray(), CC::fgGreen());
            description = "A (more or less) robust shield, made of wood.";
            break;
        }
        break;
    }
    case Ressources::Items::EQuality::eGood:
    case Ressources::Items::EQuality::eAwesomne:
    {
        switch (Randomizer::getRandom(5))
        {
        case 0:
        default:
            names = {"Round Shield", "Round Shield + 1", "Round Shield +2", "Round Shield +3", "Round Shield +4"};
            colorizeNames(names, CC::fgYellow(), CC::fgCyan());
            description = "A Buckler, a small, round, savage shield.";
            break;
        case 1:
            names = {"Tower Shield", "Tower Shield +1", "Tower Shield +2", "Tower Shield +3", "Tower Shield +4"};
            colorizeNames(names, CC::fgRed(), CC::fgYellow());
            description = "A large, robust heavy shield";
            break;
        case 2:
            names = {"Spiked Shield", "Spiked Shield +1", "Spiked Shield +2", "Spiked Shield +3", "Spiked Shield +4"};
            colorizeNames(names, CC::fgRed(), CC::fgLightGreen());
            description = "A shield, with spikes, 'nuff saif.";
            break;
        case 3:
            names = {"Metal Shield", "Metal Shield +1", "Metal Shield +2", "Metal Shield +3", "Metal Shield +4"};
            colorizeNames(names, CC::fgLightCyan(), CC::fgCyan());
            description = "A shield made of metal, for maximum protection";
            break;
        case 4:
            names = {"Elbow Shield", "Elbow Shield +1", "Elbow Shield +2", "Elbow Shield +3", "Elbow Shield +4"};
            colorizeNames(names, CC::fgLightYellow(), CC::fgYellow());
            description = "A shield attached to your arm for better movement.";
            break;
        }
        break;
    }
    }

    return std::make_pair(names, description);
}

std::pair<std::vector<std::string>, std::string> getRandomArmorNamesAndDescription(
    const Ressources::Items::EQuality quality)
{
    std::vector<std::string> names;
    std::string description;

    switch (quality)
    {
    case Ressources::Items::EQuality::eJunk:
    default:
        names = {"Ripped T-Shirt", "White T-Shirt", "Fashionable T-Shirt"};
        colorizeNames(names, CC::fgLightGray(), CC::ccReset());
        description = "Looks like mere clothing, but should offer a little protection.";
        break;
    case Ressources::Items::EQuality::eFair:
    {
        switch (Randomizer::getRandom(3))
        {
        case 0:
        default:
            names = {"Ripped Wolf Fur", "Repaired Wolf Fur", "Wolf Fur", "Fur of the Alpha Wolf"};
            colorizeNames(names, CC::fgDarkGray(), CC::fgLightGray());
            description = "The fur of a wolf, perfect protection";
            break;
        case 1:
            names = {"Some Leather Sheets", "Leather Tunic", "Lether Clothes", "Leather Armor"};
            colorizeNames(names, CC::fgRed(), CC::fgLightGreen());
            description = "Good Sturdy Leather for good sturdy protection";
            break;
        case 2:
            names = {"Felt Shirt", "Felt Clothing", "Felt Jacket", "Felt Armor"};
            colorizeNames(names, CC::fgCyan(), CC::fgLightBlue());
            description = "Clothes made of felt. It can protect a pen, it can protect you";
            break;
        }
        break;
    }
    case Ressources::Items::EQuality::eGood:
    case Ressources::Items::EQuality::eAwesomne:
    {
        switch (Randomizer::getRandom(4))
        {
        case 0:
        default:
            names = {"Chain Mail", "Chain Mail +1", "Chain Mail +2", "Chain Mail +3", "Chain Mail +4"};
            colorizeNames(names, CC::fgLightBlue(), CC::fgLightGray());
            description = "A nice, handcrafted chain mail. good against swords and clubs.";
            break;
        case 1:
            names = {"Plate Mail", "Plate Mail +1", "Plate Mail +2", "Plate Mail +3", "Plate Mail +4"};
            colorizeNames(names, CC::fgLightCyan(), CC::fgLightYellow());
            description = "A knights' plate mail. Looks royal and protective";
            break;
        case 2:
            names = {"Scale Armor", "Scale Armor +1", "Scale Armor +2", "Scale Armor +3", "Scale Armor +4"};
            colorizeNames(names, CC::fgLightYellow(), CC::fgYellow());
            description = "Clothes made of felt. It can protect a pen, it can protect you";
            break;
        case 3:
            names = {"Robe", "Robe +1", "Robe +2", "Robe +3", "Robe +4"};
            colorizeNames(names, CC::fgLightBlue(), CC::fgRed());
            description = "Clothes made of felt. It can protect a pen, it can protect you";
            break;
        case 4:
            names = {"Spiked Armor", "Spiked Armor +1", "Spiked Armor +2", "Spiked Armor +3", "Spiked Armor +4"};
            colorizeNames(names, CC::fgCyan(), CC::fgGreen());
            description = "A armor made of leather, with spikes.";
            break;
        }
        break;
    }
    }

    return std::make_pair(names, description);
}

} // namespace

std::pair<std::vector<std::string>, std::string> Ressources::Items::getRandomEquipmentNamesAndDescription(
    const EType type, const EQuality quality)
{

    if (type == EType::eWeapon)
    {
        return getRandomSwordNamesAndDescription(quality);
    }
    if (type == EType::eShield)
    {
        return getRandomShieldNamesAndDescription(quality);
    }
    if (type == EType::eArmor)
    {
        return getRandomArmorNamesAndDescription(quality);
    }

    return {};
}

std::string Ressources::Game::fiego()
{
    return std::format("{}Fiego{}", CC::fgLightGreen(), CC::ccReset());
}

std::string Ressources::Game::brock()
{
    return std::format("{}The B-{}Rock{}", CC::fgLightGray(), CC::fgDarkGray(), CC::ccReset());
}

std::string Ressources::Game::princessLayla()
{
    return std::format("{}Princess {}{}", CC::fgLightMagenta(), layla(), CC::ccReset());
}

std::string Ressources::Game::layla()
{
    return std::format("{0}L{1}ayla{2}", CC::fgLightMagenta(), CC::fgLightBlue(), CC::ccReset());
}

std::string Ressources::Game::fishingFritz()
{
    return std::format("F{0}ishing{1} F{0}ritz{2}", CC::fgBlue(), CC::fgWhite(), CC::ccReset());
}

std::string Ressources::Game::mobi()
{
    return std::format("{}Dark {}Mo{}bi{}", CC::fgDarkGray(), CC::fgMagenta(), CC::fgLightMagenta(), CC::ccReset());
}

std::pair<std::string, std::string> Ressources::Rooms::getCapital()
{
    return std::make_pair(
        "Drerachi, The Dream City",
        "The capital of the land. Big houses, the Kings' Castle, a Kathedral, everything a glorious capital needs.");
}

std::string Ressources::Rooms::getCapitalRejection()
{
    return std::format(
        "The {}Guard{} looks at you, and shakes his head. \"Not on the list!\", is all he says. \"What list?\" you "
        "ask. \"The one, you are not on.\". is the reply making clear, that people like you are not wanted here. You "
        "think about it for a short while, and realize, that you don't even have a name. so what should they even "
        "write on their list? So probably, everything is in perfect order.",
        CC::fgLightRed(),
        CC::ccReset());
}

std::string Ressources::Game::kingJesster()
{
    return std::format("{}King {}Jes{}ster{}", CC::fgRed(), CC::fgLightGreen(), CC::fgRed(), CC::ccReset());
}

std::string Ressources::Game::laylasRibbon()
{
    return std::format("{}R{}i{}bbon{}", CC::fgMagenta(), CC::fgWhite(), CC::fgLightMagenta(), CC::ccReset());
}

std::string Ressources::Game::bimmelchen()
{
    return std::format("{0}B{1}immelchen{2}", CC::fgLightBlue(), CC::fgLightMagenta(), CC::ccReset());
}

std::string Ressources::Game::pimmelchen()
{
    return std::format("{1}P{0}immelchen{2}", CC::fgLightBlue(), CC::fgLightMagenta(), CC::ccReset());
}

std::string Ressources::Game::dancingBard()
{
    return std::format("{}Dan{}cing {}Bard{}", CC::fgRed(), CC::fgLightRed(), CC::fgGreen(), CC::ccReset());
}
