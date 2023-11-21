#include "citemfactory.h"
#include "carmor.h"
#include "cbomb.h"
#include "cequipment.h"
#include "chealingpotion.h"
#include "cheartcontainer.h"
#include "citem.h"
#include "cjunkitem.h"
#include "cphoenixfeather.h"
#include "cshield.h"
#include "cweapon.h"
#include "forest/curzasglasses.h"
#include "randomizer.h"

#include <algorithm>
#include <vector>

CItem* CItemFactory::makeShopItem()
{
    std::vector<EItemType> items = {EItemType::eHealingPotionS,  EItemType::eHealingPotionS, EItemType::eHealingPotionS,
                                    EItemType::eHealingPotionS,  EItemType::eHealingPotionS, EItemType::eHealingPotionS,
                                    EItemType::eHealingPotionS,  EItemType::eHealingPotionS,

                                    EItemType::eBombS,           EItemType::eBombS,          EItemType::eBombS,
                                    EItemType::eBombS,           EItemType::eBombS,          EItemType::eBombS,
                                    EItemType::eBombS,           EItemType::eBombS,

                                    EItemType::eHealingPotionM,  EItemType::eHealingPotionM, EItemType::eHealingPotionM,
                                    EItemType::eHealingPotionM,

                                    EItemType::eBombM,           EItemType::eBombM,          EItemType::eBombM,
                                    EItemType::eBombM,

                                    EItemType::eHealingPotionL,  EItemType::eHealingPotionL, EItemType::eBombL,
                                    EItemType::eBombL,

                                    EItemType::eHealingPotionXL, EItemType::eBombXL,         EItemType::eHeartContainer,
                                    EItemType::ePhoenixFeather};

    std::shuffle(items.begin(), items.end(), std::default_random_engine(Randomizer::getRandomEngineSeed()));
    return makeItem(items.at(0));
}

CItem* CItemFactory::makeAwesomneItem()
{
    std::vector<EItemType> items = {EItemType::eUrzasGlasses,

                                    EItemType::ePhoenixFeather,
                                    EItemType::ePhoenixFeather,
                                    EItemType::ePhoenixFeather,

                                    EItemType::eHeartContainer,
                                    EItemType::eHeartContainer,
                                    EItemType::eHeartContainer};

    std::shuffle(items.begin(), items.end(), std::default_random_engine(Randomizer::getRandomEngineSeed()));
    return makeItem(items.at(0));
}

CItem* CItemFactory::makeEquipment(const Ressources::Items::EType type, const Ressources::Items::EQuality quality)
{
    switch (type)
    {
    case Ressources::Items::EType::eWeapon:
    default:
        return new CWeapon(quality);
    case Ressources::Items::EType::eShield:
        return new CShield(quality);
    case Ressources::Items::EType::eArmor:
        return new CArmor(quality);
    }
}

void CItemFactory::registerLootItemGenerator(const std::string_view& moduleName,
                                             LootItemGeneratorFunction generatorFunction,
                                             const unsigned int dropRate)
{
    LootItemGenerator generator;
    generator.moduleName = moduleName;
    generator.lootGenerator = generatorFunction;
    generator.dropRate = dropRate;

    _lootGenerators.push_back(generator);
}

void CItemFactory::unregisterLootItemGeneratorByName(const std::string_view& moduleName)
{
    auto it = std::remove_if(_lootGenerators.begin(), _lootGenerators.end(), LootItemGenerator::nameFilter(moduleName));
    _lootGenerators.erase(it);
}

CItem* CItemFactory::makeItem(const EItemType tp)
{
    switch (tp)
    {
    case EItemType::eHealingPotionS:
        return new CHealingPotion(CHealingPotion::PotionSize::S);
    case EItemType::eHealingPotionM:
        return new CHealingPotion(CHealingPotion::PotionSize::M);
    case EItemType::eHealingPotionL:
        return new CHealingPotion(CHealingPotion::PotionSize::L);
    case EItemType::eHealingPotionXL:
        return new CHealingPotion(CHealingPotion::PotionSize::XL);

    case EItemType::eBombS:
        return new CBomb(CBomb::BombSize::S);
    case EItemType::eBombM:
        return new CBomb(CBomb::BombSize::M);
    case EItemType::eBombL:
        return new CBomb(CBomb::BombSize::L);
    case EItemType::eBombXL:
        return new CBomb(CBomb::BombSize::XL);

    case EItemType::ePhoenixFeather:
        return new CPhoenixFeather();
    case EItemType::eHeartContainer:
        return new CHeartContainer;
    case EItemType::eJunkItem:
        return new CJunkItem();
    case EItemType::eUrzasGlasses:
        return new CUrzasGlasses();
    default:
        return nullptr;
    }
    return nullptr;
}

CItem* CItemFactory::makeShopEquipment(const unsigned int playerLevel)
{
    unsigned int levelModifier = playerLevel;
    if (levelModifier > 15)
    {
        levelModifier = 15;
    }

    Ressources::Items::EType type;
    Ressources::Items::EQuality quality;

    switch (Randomizer::getRandom(3))
    {
    case 0:
    default:
        type = Ressources::Items::EType::eArmor;
        break;
    case 1:
        type = Ressources::Items::EType::eShield;
        break;
    case 2:
        type = Ressources::Items::EType::eWeapon;
        break;
    }

    if (Randomizer::getRandom(10) + levelModifier >= 20)
    {
        quality = Ressources::Items::EQuality::eGood;
    }
    else
    {
        quality = Ressources::Items::EQuality::eFair;
    }

    return makeEquipment(type, quality);
}

CItem* CItemFactory::makeLootItem()
{
    if (_lootGenerators.size() == 0)
    {
        return makeItem(EItemType::eJunkItem);
    }

    unsigned int index = 0;
    std::vector<unsigned int> indices;
    for (const auto& gen : _lootGenerators)
    {
        for (int j = 0; j < gen.dropRate; j++)
        {
            indices.push_back(index);
        }
    }
    if (indices.size() == 0)
    {
        return makeItem(EItemType::eJunkItem);
    }

    auto randomIndex = Randomizer::getRandom(indices.size() * 2);

    if (randomIndex < indices.size())
    {
        return _lootGenerators.at(indices.at(randomIndex)).lootGenerator();
    }

    return makeItem(EItemType::eJunkItem);
}
