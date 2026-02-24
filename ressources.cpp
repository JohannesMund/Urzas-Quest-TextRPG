#include "ressources.h"
#include "colorize.h"
#include "ctranslator.h"
#include "randomizer.h"

#include <algorithm>
#include <format>
#include <map>

namespace
{
template <typename... Args>
std::string tr(const std::string_view& textId, Args&&... formatArgs)
{
    return CTranslator::tr(TagNames::Translator::core, TagNames::Translator::ressources, textId, formatArgs...);
}
std::string tr(const std::string_view& textId)
{
    return CTranslator::tr(TagNames::Translator::core, TagNames::Translator::ressources, textId);
}

} // namespace

std::string Ressources::Rooms::getRandomDescription()
{
    return Randomizer::getRandomStringFromVector(
        {tr("A Meadow. With grass. A lot of grass. It is green. Did i mention the grass? Oh, there is a sheep. Do you "
            "like "
            "sheep? I like sheep. There is one."),

         tr("A deep, dark Forest. Trees and Bushes around you. The ground is muddy and wet. Was that a fairy? Maybe a "
            "forest "
            "fairy? In this case, her name is probably \"Holla\"."),

         tr("The shore of a lake. This is one big lake, so big, that it should be called \"Lake Enormous\". But it is "
            "just "
            "a "
            "lake. On second glance, not even a big one.")});
}

std::pair<std::string, std::string> Ressources::Items::getRandomJunkItems()
{
    std::vector<std::pair<std::string, std::string>> items = {
        {{tr("{}Stick{}", CC::fgYellow(), CC::ccReset())},
         {tr("A stick, just a stick. Maybe magical? There is no label stating \"Godly Magic Stick of the "
             "Whale\". On the "
             "other hand, there no label stating, that this stick is not a \"Godly Magic Stick of the Whale\".")}},
        {{sock()},
         {tr("A single sock. A single dirty sock. Useless without the other one. Who on earth throws away a "
             "single Sock??")}},
        {{otherSock()},
         {tr("There it is, the other sock. A single dirty sock. Now you have both but who on earth throws away two "
             "single "
             "Socks seperately??")}},
        {{tr("{}Rock{}", CC::fgCyan(), CC::ccReset())},
         {tr("This is a good rock, so good, that it might be used in an epic \"Rock Paper Sicsors\" battle.")}},
        {{tr("{}Boot{}", CC::fgYellow(), CC::ccReset())},
         {tr("An old, single boot made from leather.Good, expensive leather. But is damaged and dirty. And it is just "
             "a single boot.")}},
        {{tr("V{0}a{1}s{0}e{1}", CC::fgBlue(), CC::ccReset())},
         {tr("This is one beautiful vase. It will look nice on your table. or on a sideboard. you could fill it with "
             "flowers. Or you just throw it away, for somone else to find ist.")}},
        {{tr("Flask")},
         {tr("An empty flask. Like the ones filled with magic potions, only without the potion. This one is filled "
             "with "
             "nothing.")}},
        {{tr("{0}Col{1}l{2}ec{0}tio{1}n o{0}f l{3}eav{1}es{4}",
             CC::fgYellow(),
             CC::fgLightYellow(),
             CC::fgLightGreen(),
             CC::fgLightRed(),
             CC::ccReset())},
         {tr("A collection of especially beautiful leaves.")}},
        {{tr("{}Ring{}", CC::fgYellow(), CC::ccReset())},
         {tr("A ring, probably from a bubblegum machine (What is a bubble gum machine?), anyway, nothing for "
             "proposing to {}.",
             Game::princessLeila())}}};

    return items.at(Randomizer::getRandom((unsigned int)items.size()));
}

Ressources::Items::EFlower Ressources::Items::getRandomFlowerType()
{
    std::vector<EFlower> flowers;
    for (auto i : FlowerIterator())
    {
        flowers.push_back(i);
    }

    return Randomizer::getRandomEntry(flowers);
}

std::string Ressources::Items::flower2String(const EFlower& flower)
{
    switch (flower)
    {
    case EFlower::eRose:
        return CC::colorizeString(tr("Rose"), CC::fgRed(), CC::fgLightRed());
    case EFlower::eCornFlower:
        return CC::colorizeString(tr("Cornflower"), CC::fgLightCyan(), CC::fgBlue());
    case EFlower::ePrimeRose:
        return CC::colorizeString(tr("Primerose"), CC::fgYellow(), CC::fgLightYellow());
    case EFlower::eTulip:
        return CC::colorizeString(tr("Tulip"), CC::fgMagenta(), CC::fgLightRed());
    case EFlower::eSunflower:
        return CC::colorizeString(tr("Sunflower"), CC::fgYellow(), CC::fgLightRed());
    case EFlower::eCarnationFlower:
        return CC::colorizeString(tr("Carnationflower"), CC::fgLightMagenta(), CC::fgWhite());
    case EFlower::ePansy:
        return CC::colorizeString(tr("Pansy"), CC::fgBlack(), CC::fgBlue());
    case EFlower::eDaisy:
        return CC::colorizeString(tr("Daisy"), CC::fgYellow(), CC::fgWhite());
    case EFlower::eOrchid:
        return CC::colorizeString(tr("Orchid"), CC::fgMagenta(), CC::fgLightMagenta());
    case EFlower::eUnknown:
    default:
        return CC::colorizeString(tr("Blob From outer space"), CC::fgGreen(), CC::fgLightRed());
    }
}

int Ressources::Items::flower2Value(const EFlower& flower)
{
    switch (flower)
    {
    case EFlower::eRose:
        return 10;
    case EFlower::eCornFlower:
        return 3;
    case EFlower::ePrimeRose:
        return 1;
    case EFlower::eTulip:
        return 7;
    case EFlower::eSunflower:
        return 8;
    case EFlower::eCarnationFlower:
        return 2;
    case EFlower::ePansy:
        return 2;
    case EFlower::eDaisy:
        return 1;
    case EFlower::eOrchid:
        return 18;
    case EFlower::eUnknown:
    default:
        return 10000;
    }
}

std::string Ressources::Enemies::getRandomEnemyName()
{
    return Randomizer::getRandomStringFromVector({tr("Bob, the Cowboy"),
                                                  tr("Eddie, the Cowboy"),
                                                  tr("Angry Rat"),
                                                  tr("Stinky Bat"),
                                                  tr("Greedy Vulture"),
                                                  tr("Huge Barbarian"),
                                                  tr("Pussy, the Octopus"),
                                                  tr("Tentacool"),
                                                  tr("Tentacruel"),
                                                  tr("Kang"),
                                                  tr("Kodos")});
}

std::string Ressources::Enemies::getRandomEnemyWeapon()
{
    return Randomizer::getRandomStringFromVector({tr("shabby board with a rusty nail hammered through"),
                                                  tr("sharp teeth"),
                                                  tr("sheer muscle power"),
                                                  tr("a club with spikes"),
                                                  tr("a Nokia 3210"),
                                                  tr("tantacles"),
                                                  tr("laser gun")});
}

std::pair<std::string, std::string> Ressources::Rooms::getRandomTown()
{
    std::vector<std::pair<std::string, std::string>> towns = {
        {"Hafnarfjodur", tr("The City of Elves. Built high in the treetops of ancient Trees")},
        {"Peridotspring", tr("Deep Caves, carved in huge mountains built this citiy of the dwarfs")},
        {"Wallachia", tr("An Oasis surrounded by a huge desert.")},
        {"Bruchtal", tr("City of man, capital of the land.")},
        {"Mudpool", tr("The Home of the trolls. Everything is dirty and stinky here.")},
        {"Timbuktu",
         tr("The mysterous city, where the pepper grows. Many legendary heroes have been sent here. But on second "
            "sight, "
            "it is just a city.")}};
    return towns.at((unsigned int)Randomizer::getRandom(towns.size()));
}

std::string Ressources::Companion::nameForCompanionType(const ECompanionType& tp, const unsigned int level)
{
    std::map<ECompanionType, std::vector<std::string>> companions = {
        {ECompanionType::eHealer, {tr("Chick"), tr("Sparrow"), tr("Parrot"), tr("Griffon"), tr("Phoenix")}},
        {ECompanionType::eDefender, {tr("Whelp"), tr("Dog"), tr("Wolf"), tr("Ice wolf"), tr("Cerberus")}},
        {ECompanionType::eAttacker, {tr("Kitten"), tr("Cat"), tr("Lynx"), tr("Tiger"), tr("Sphinx")}},
        {ECompanionType::eScaryMonster,
         {tr("Baby Dragon"), tr("Young Dragon"), tr("Adult Dragon"), tr("Old Dragon"), tr("Ancient Hellfire Dragon")}}};

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
        {tr("Fat Eddie"), tr("Blackmailing the Mayor")},
        {tr("Robo Devil"), tr("Stealing people's hands")},
        {tr("Evil Wizard"), tr("Doing evil wizard things")},
        {tr("Robin Would"), tr("Stealing from the rich")},
        {tr("Taffy, the Pirate"), tr("Crimes against the world government")}};
    return names.at((unsigned int)Randomizer::getRandom(names.size()));
}

std::string Ressources::Rooms::getRandomRumor()
{
    return Randomizer::getRandomStringFromVector({tr("The king has stupid ears."),
                                                  tr("There is a huge treasure hidden beneath the mountain."),
                                                  tr("The mayor of this town has an affair with a donkey.")});
}

std::string Ressources::Game::whoTheFuckIsUrza()
{
    return tr("{}wh{}o t{}he f{}uck {}is {}?{}",
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
    return tr("{}Ur{}za{}", CC::fgLightGreen(), CC::fgYellow(), CC::ccReset());
}

std::string Ressources::Game::urzaWhoTheFuckIsUrza()
{
    return tr("{} {}", urza(), whoTheFuckIsUrza());
}

std::string Ressources::Items::sock()
{
    return tr("{}S{}o{}c{}k{}", CC::fgRed(), CC::fgYellow(), CC::fgRed(), CC::fgYellow(), CC::ccReset());
}
std::string Ressources::Items::otherSock()
{
    return tr("{}The other {}S{}o{}c{}k{}",
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
        names = {tr("Stick, shaped like a sword"), tr("Sword, shaped like a stick"), tr("Stick-Sword")};
        colorizeNames(names, CC::fgGreen(), CC::fgYellow());
        description = tr("A stick, shaped like a sword. Or a sword, shaped like a stick? It is a sword-stick");
        break;
    case Ressources::Items::EQuality::eFair:
    {
        switch (Randomizer::getRandom(3))
        {
        case 0:
        default:
            names = {tr("Trunk"), tr("Club"), tr("Big Club"), tr("Metal-plated Club")};
            colorizeNames(names, CC::fgYellow(), CC::fgLightYellow());
            description = tr("A big trunk, used as club. Clubby cluby ouchie ouchie");
            break;
        case 1:
            names = {tr("Steak Knife"), tr("Dagger"), tr("Polished Dagger"), tr("Pointy Dagger")};
            colorizeNames(names, CC::fgLightBlue(), CC::fgLightCyan());
            description = tr("A good steak knife. Usable as a dagger.");
            break;
        case 2:
            names = {tr("Fighting Stick"), tr("Fighting Staff"), tr("Enhanced Fighting Staff"), tr("Battle staff")};
            colorizeNames(names, CC::fgLightYellow(), CC::fgYellow());
            description = tr("A Stick, usable for fighting");
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
            names = {tr("Sword"), tr("Sword +1"), tr("Sword +2"), tr("Sword +3"), tr("Sword +4")};
            colorizeNames(names, CC::fgRed(), CC::fgYellow());
            description = tr("This is one good sword. Made for a glorious knight");
            break;
        case 1:
            names = {tr("Mace"), tr("Mace +1"), tr("Mace +2"), tr("Mace +3"), tr("Mace +4")};
            colorizeNames(names, CC::fgBlue(), CC::fgLightBlue());
            description = tr("A Mace, like the onse used by the battle clerics of the king.");
            break;
        case 2:
            names = {tr("Halberd"), tr("Halberd +1"), tr("Halberd +2"), tr("Halberd +3"), tr("Halberd +4")};
            colorizeNames(names, CC::fgLightRed(), CC::fgLightGray());
            description = tr("A large Halberd, made for the Kings guards");
            break;
        case 3:
            names = {tr("Dagger"), tr("Dagger +1"), tr("Dagger +2"), tr("Dagger +3"), tr("Dagger +4")};
            colorizeNames(names, CC::fgLightGray(), CC::fgDarkGray());
            description = tr("An awesomne, hand-crafted Dagger, fast and deadly");
            break;
        case 4:
            names = {tr("Whip"), tr("Whip +1"), tr("Whip +2"), tr("Whip +3"), tr("Whip +4")};
            colorizeNames(names, CC::fgLightMagenta(), CC::fgRed());
            description = tr("Who fights with a whip? Everybody should, considering the reach of this beast");
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
            names = {tr("godly Stick of the Whale"),
                     tr("godly Stick of the Whale +1"),
                     tr("godly Stick of the Whale +2"),
                     tr("godly Stick of the Whale +3"),
                     tr("godly Stick of the Whale +4"),
                     tr("godly Stick of the Whale +5"),
                     tr("godly Stick of the Whale +6"),
                     tr("godly Stick of the Whale +7"),
                     tr("godly Stick of the Whale +8")};
            colorizeNames(names, CC::fgBlue(), CC::fgLightBlue());
            description =
                tr("Its a stick, but other than the other sticks, it has a label \"godly Stick of the Whale\"");
            break;
        case 1:
            names = {tr("antique Sword of the Ancients"),
                     tr("antique Sword of the Ancients +1"),
                     tr("antique Sword of the Ancients +2"),
                     tr("antique Sword of the Ancients +3"),
                     tr("antique Sword of the Ancients +4"),
                     tr("antique Sword of the Ancients +5"),
                     tr("antique Sword of the Ancients +6"),
                     tr("antique Sword of the Ancients +7"),
                     tr("antique Sword of the Ancients +8")};
            colorizeNames(names, CC::fgYellow(), CC::fgLightYellow());
            description = tr("This is one really really old and magic sword.");
            break;
        case 2:
            names = {
                tr("Trident of the Demon king"),
                tr("Trident of the Demon king +1"),
                tr("Trident of the Demon king +2"),
                tr("Trident of the Demon king +3"),
                tr("Trident of the Demon king +4"),
                tr("Trident of the Demon king +5"),
                tr("Trident of the Demon king +6"),
                tr("Trident of the Demon king +7"),
                tr("Trident of the Demon king +8"),
            };
            colorizeNames(names, CC::fgRed(), CC::fgDarkGray());
            description = tr("A cool trident, the spikes seem to glow, and they are hot! well, not as hot as {}.",
                             Ressources::Game::leila());
            break;
        case 3:
            names = {tr("Whip of the beast tamer"),
                     tr("Whip of the beast tamer +1"),
                     tr("Whip of the beast tamer +2"),
                     tr("Whip of the beast tamer +3"),
                     tr("Whip of the beast tamer +4"),
                     tr("Whip of the beast tamer +5"),
                     tr("Whip of the beast tamer +6"),
                     tr("Whip of the beast tamer +7"),
                     tr("Whip of the beast tamer +8")};
            colorizeNames(names, CC::fgLightGray(), CC::fgYellow());
            description =
                tr("This whip has certainly tamed many beasts. Who knows, maybe it works on a certain princess?");
            break;
        case 4:
            names = {tr("Holy mace of the Nephalim"),
                     tr("Holy mace of the Nephalim +1"),
                     tr("Holy mace of the Nephalim +2"),
                     tr("Holy mace of the Nephalim +3"),
                     tr("Holy mace of the Nephalim +4"),
                     tr("Holy mace of the Nephalim +5"),
                     tr("Holy mace of the Nephalim +6"),
                     tr("Holy mace of the Nephalim +7"),
                     tr("Holy mace of the Nephalim +8")};
            colorizeNames(names, CC::fgLightYellow(), CC::fgLightGray());
            description = tr("A mace, so holy, you can stick a tail on it, and call it a beaver.");
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
        names = {tr("wheathered wooden board"), tr("wooden board"), tr("robust wooden board")};
        colorizeNames(names, CC::fgYellow(), CC::fgLightRed());
        description =
            tr("A wooden board. It can protect you from... well, not much but it offers a little protection.");
        break;
    case Ressources::Items::EQuality::eFair:
    {
        switch (Randomizer::getRandom(3))
        {
        case 0:
        default:
            names = {tr("Damaged Buckler"), tr("Repaired Buckler"), tr("Buckler"), tr("Shiny Buckler")};
            colorizeNames(names, CC::fgYellow(), CC::fgCyan());
            description = tr("A Buckler, a small, round, savage shield.");
            break;
        case 1:
            names = {tr("Ripped Leather Shield"),
                     tr("Repaired Leather Shield"),
                     tr("Leather Shield"),
                     tr("Shiny Leather Shield")};
            colorizeNames(names, CC::fgRed(), CC::fgYellow());
            description = tr("A shield made of leather, light and sturdy.");
            break;
        case 2:
            names = {tr("Brittle Wooden Shield"),
                     tr("Repaired Wooden Shield"),
                     tr("Wooden Shield"),
                     tr("Shiny Wooden Shield")};
            colorizeNames(names, CC::fgLightGray(), CC::fgGreen());
            description = tr("A (more or less) robust shield, made of wood.");
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
            names = {tr("Round Shield"),
                     tr("Round Shield + 1"),
                     tr("Round Shield +2"),
                     tr("Round Shield +3"),
                     tr("Round Shield +4")};
            colorizeNames(names, CC::fgYellow(), CC::fgCyan());
            description = tr("A Buckler, a small, round, savage shield.");
            break;
        case 1:
            names = {tr("Tower Shield"),
                     tr("Tower Shield +1"),
                     tr("Tower Shield +2"),
                     tr("Tower Shield +3"),
                     tr("Tower Shield +4")};
            colorizeNames(names, CC::fgRed(), CC::fgYellow());
            description = tr("A large, robust heavy shield");
            break;
        case 2:
            names = {tr("Spiked Shield"),
                     tr("Spiked Shield +1"),
                     tr("Spiked Shield +2"),
                     tr("Spiked Shield +3"),
                     tr("Spiked Shield +4")};
            colorizeNames(names, CC::fgRed(), CC::fgLightGreen());
            description = tr("A shield, with spikes, 'nuff saif.");
            break;
        case 3:
            names = {tr("Metal Shield"),
                     tr("Metal Shield +1"),
                     tr("Metal Shield +2"),
                     tr("Metal Shield +3"),
                     tr("Metal Shield +4")};
            colorizeNames(names, CC::fgLightCyan(), CC::fgCyan());
            description = tr("A shield made of metal, for maximum protection");
            break;
        case 4:
            names = {tr("Elbow Shield"),
                     tr("Elbow Shield +1"),
                     tr("Elbow Shield +2"),
                     tr("Elbow Shield +3"),
                     tr("Elbow Shield +4")};
            colorizeNames(names, CC::fgLightYellow(), CC::fgYellow());
            description = tr("A shield attached to your arm for better movement.");
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
        names = {tr("Ripped T-Shirt"), tr("White T-Shirt"), tr("Fashionable T-Shirt")};
        colorizeNames(names, CC::fgLightGray(), CC::ccReset());
        description = tr("Looks like mere clothing, but should offer a little protection.");
        break;
    case Ressources::Items::EQuality::eFair:
    {
        switch (Randomizer::getRandom(3))
        {
        case 0:
        default:
            names = {tr("Ripped Wolf Fur"), tr("Repaired Wolf Fur"), tr("Wolf Fur"), tr("Fur of the Alpha Wolf")};
            colorizeNames(names, CC::fgDarkGray(), CC::fgLightGray());
            description = tr("The fur of a wolf, perfect protection");
            break;
        case 1:
            names = {tr("Some Leather Sheets"), tr("Leather Tunic"), tr("Lether Clothes"), tr("Leather Armor")};
            colorizeNames(names, CC::fgRed(), CC::fgLightGreen());
            description = tr("Good Sturdy Leather for good sturdy protection");
            break;
        case 2:
            names = {tr("Felt Shirt"), tr("Felt Clothing"), tr("Felt Jacket"), tr("Felt Armor")};
            colorizeNames(names, CC::fgCyan(), CC::fgLightBlue());
            description = tr("Clothes made of felt. It can protect a pen, it can protect you");
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
            names = {
                tr("Chain Mail"), tr("Chain Mail +1"), tr("Chain Mail +2"), tr("Chain Mail +3"), tr("Chain Mail +4")};
            colorizeNames(names, CC::fgLightBlue(), CC::fgLightGray());
            description = tr("A nice, handcrafted chain mail. good against swords and clubs.");
            break;
        case 1:
            names = {
                tr("Plate Mail"), tr("Plate Mail +1"), tr("Plate Mail +2"), tr("Plate Mail +3"), tr("Plate Mail +4")};
            colorizeNames(names, CC::fgLightCyan(), CC::fgLightYellow());
            description = tr("A knights' plate mail. Looks royal and protective");
            break;
        case 2:
            names = {tr("Scale Armor"),
                     tr("Scale Armor +1"),
                     tr("Scale Armor +2"),
                     tr("Scale Armor +3"),
                     tr("Scale Armor +4")};
            colorizeNames(names, CC::fgLightYellow(), CC::fgYellow());
            description = tr("Clothes made of felt. It can protect a pen, it can protect you");
            break;
        case 3:
            names = {tr("Robe"), tr("Robe +1"), tr("Robe +2"), tr("Robe +3"), tr("Robe +4")};
            colorizeNames(names, CC::fgLightBlue(), CC::fgRed());
            description = tr("Clothes made of felt. It can protect a pen, it can protect you");
            break;
        case 4:
            names = {tr("Spiked Armor"),
                     tr("Spiked Armor +1"),
                     tr("Spiked Armor +2"),
                     tr("Spiked Armor +3"),
                     tr("Spiked Armor +4")};
            colorizeNames(names, CC::fgCyan(), CC::fgGreen());
            description = tr("A armor made of leather, with spikes.");
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
    return tr("{}Fiego{}", CC::fgLightGreen(), CC::ccReset());
}

std::string Ressources::Game::brock()
{
    return tr("{}The B-{}Rock{}", CC::fgLightGray(), CC::fgDarkGray(), CC::ccReset());
}

std::string Ressources::Game::princessLeila()
{
    return tr("{}Princess {}{}", CC::fgLightMagenta(), leila(), CC::ccReset());
}

std::string Ressources::Game::leila()
{
    return tr("{0}L{1}eila{2}", CC::fgLightMagenta(), CC::fgLightBlue(), CC::ccReset());
}

std::string Ressources::Game::fishingFritz()
{
    return tr("F{0}ishing{1} F{0}ritz{2}", CC::fgBlue(), CC::fgWhite(), CC::ccReset());
}

std::string Ressources::Game::mobi()
{
    return tr("{}Mo{}bi{}", CC::fgMagenta(), CC::fgLightMagenta(), CC::ccReset());
}

std::string Ressources::Game::darkMobi()
{
    return tr("{}Dark {}", CC::fgDarkGray(), mobi());
}

std::pair<std::string, std::string> Ressources::Rooms::getCapital()
{
    return std::make_pair(tr("Drerachi, The Dream City"),
                          tr("The capital of the land. Big houses, the Kings' Castle, a Kathedral, everything a "
                             "glorious capital needs."));
}

std::string Ressources::Rooms::getCapitalRejection()
{
    return tr(
        "The {}Guard{} looks at you, and shakes his head. \"Not on the list!\", is all he says. \"What list?\" you "
        "ask. \"The one, you are not on.\". is the reply making clear, that people like you are not wanted here. You "
        "think about it for a short while, and realize, that you don't even have a name. so what should they even "
        "write on their list? So probably, everything is in perfect order.",
        CC::fgLightRed(),
        CC::ccReset());
}

std::string Ressources::Game::kingJesster()
{
    return tr("{}King {}Jes{}ster{}", CC::fgRed(), CC::fgLightGreen(), CC::fgRed(), CC::ccReset());
}

std::string Ressources::Game::leilasRibbon()
{
    return tr("{}R{}i{}bbon{}", CC::fgMagenta(), CC::fgWhite(), CC::fgLightMagenta(), CC::ccReset());
}

std::string Ressources::Game::piefke()
{
    return tr("{0}Pi{1}ef{0}ke{2}", CC::fgBlue(), CC::fgYellow(), CC::ccReset());
}

std::string Ressources::Game::schniefke()
{
    return tr("{1}Sch{0}nie{1}fke{2}", CC::fgBlue(), CC::fgYellow(), CC::ccReset());
}

std::string Ressources::Game::bimmel()
{
    return tr("{0}Bi{1}mm{0}el{2}", CC::fgBlue(), CC::fgYellow(), CC::ccReset());
}

std::string Ressources::Game::bommel()
{
    return tr("{1}Bo{0}mm{1}el{2}", CC::fgBlue(), CC::fgYellow(), CC::ccReset());
}

std::string Ressources::Game::horst()
{
    return tr("{1}H{0}or{1}st{2}", CC::fgBlue(), CC::fgYellow(), CC::ccReset());
}

std::string Ressources::Game::bimmelchen()
{
    return tr("{0}B{1}immelchen{2}", CC::fgLightBlue(), CC::fgLightMagenta(), CC::ccReset());
}

std::string Ressources::Game::pimmelchen()
{
    return tr("{1}P{0}immelchen{2}", CC::fgLightBlue(), CC::fgLightMagenta(), CC::ccReset());
}

std::string Ressources::Game::dancingBard()
{
    return tr("{}Dan{}cing {}Bard{}", CC::fgRed(), CC::fgLightRed(), CC::fgGreen(), CC::ccReset());
}
