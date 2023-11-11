#include "itemfactory.h"
#include "cbomb.h"
#include "chealingpotion.h"
#include "cheartcontainer.h"
#include "cjunkitem.h"
#include "cphoenixfeather.h"
#include "cshield.h"
#include "csword.h"
#include "forest/curzasglasses.h"
#include "randomizer.h"

#include <algorithm>
#include <vector>

namespace
{

}

CItem* ItemFactory::makeItem(const EItemType tp)
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

CItem* ItemFactory::makeShopItem()
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

CItem* ItemFactory::makeAwesomneItem()
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
