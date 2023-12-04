#include "citemfactory.h"
#include "carmor.h"
#include "cbomb.h"
#include "cequipment.h"
#include "chealingpotion.h"
#include "cheartcontainer.h"
#include "citem.h"
#include "cjunkitem.h"
#include "cphoenixfeather.h"
#include "csandwich.h"
#include "cshield.h"
#include "cweapon.h"
#include "randomizer.h"

#include <algorithm>
#include <vector>

CItem* CItemFactory::generateShopItem()
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

    return generateItem(items.at(Randomizer::getRandom(items.size())));
}

CItem* CItemFactory::makeAwesomneItem()
{
    std::vector<EItemType> items = {EItemType::ePhoenixFeather, EItemType::eHeartContainer};

    return generateItem(items.at(Randomizer::getRandom(items.size())));
}

CItem* CItemFactory::makeShopItem() const
{
    return itemFromGeneratorList(_shopGenerators, &CItemFactory::generateShopItem);
}

CSandwich* CItemFactory::sandwichMaker() const
{
    std::vector<CSandwich::EIngredients> ingredients;
    for (auto i : CSandwich::ingredientIterator())
    {
        ingredients.push_back(i);
    }

    int count = 0;

    std::vector<CSandwich::EIngredients> sandwichIngredients;

    do
    {
        sandwichIngredients.push_back(ingredients.at(Randomizer::getRandom(ingredients.size())));

        if (Randomizer::getRandom(3) == 0)
        {
            break;
        }
    } while (count < 25);

    return new CSandwich(sandwichIngredients);
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
                                             ItemGeneratorFunction generatorFunction,
                                             const unsigned int dropRate)
{
    ItemGenerator generator;
    generator.moduleName = moduleName;
    generator.lootGenerator = generatorFunction;
    generator.dropRate = dropRate;

    _lootGenerators.push_back(generator);
}

void CItemFactory::unregisterLootItemGeneratorByName(const std::string_view& moduleName)
{
    auto it = std::remove_if(_lootGenerators.begin(), _lootGenerators.end(), ItemGenerator::nameFilter(moduleName));
    if (it != _lootGenerators.end())
    {
        _lootGenerators.erase(it);
    }
}

void CItemFactory::registerShopItemGenerator(const std::string_view& moduleName,
                                             ItemGeneratorFunction generatorFunction,
                                             const unsigned int dropRate)
{
    ItemGenerator generator;
    generator.moduleName = moduleName;
    generator.lootGenerator = generatorFunction;
    generator.dropRate = dropRate;

    _shopGenerators.push_back(generator);
}

void CItemFactory::unregisterShopItemGeneratorByName(const std::string_view& moduleName)
{
    auto it = std::remove_if(_shopGenerators.begin(), _shopGenerators.end(), ItemGenerator::nameFilter(moduleName));
    if (it != _shopGenerators.end())
    {
        _shopGenerators.erase(it);
    }
}

CItem* CItemFactory::generateItem(const EItemType tp)
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

    default:
        return nullptr;
    }
    return nullptr;
}

CItem* CItemFactory::itemFromGeneratorList(const ItemGeneratorList& list,
                                           const ItemGeneratorFunction& defaultGenerator) const
{
    if (list.size() == 0)
    {
        return defaultGenerator();
    }

    unsigned int index = 0;
    std::vector<unsigned int> indices;
    for (const auto& gen : list)
    {
        for (auto j = 0U; j < gen.dropRate; j++)
        {
            indices.push_back(index);
        }
    }

    if (indices.size() == 0)
    {
        return defaultGenerator();
    }

    auto randomIndex = Randomizer::getRandom(indices.size() + 100);

    if (randomIndex < indices.size())
    {
        return list.at(indices.at(randomIndex)).lootGenerator();
    }

    return defaultGenerator();
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
    return itemFromGeneratorList(_lootGenerators, []() { return CItemFactory::generateItem(EItemType::eJunkItem); });
}
