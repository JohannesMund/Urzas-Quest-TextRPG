#include "cfishrestaurant.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorconsole.h"
#include "console.h"
#include "fishingvillage/moduleressources.h"
#include "randomizer.h"

#include <format>
#include <vector>

CFishRestaurant::CFishRestaurant()
{
}

void CFishRestaurant::execute()
{
    makeDishOfTheDay();

    CMenu::Action input;

    do
    {
        Console::cls();

        Console::printLn(std::format("{}'s Inn", FishingVillageRessources::fishingVilleName()),
                         Console::EAlignment::eCenter);
        Console::printLn(
            std::format("Serving the best fresh fish since 833 ad. dragonis", FishingVillageRessources::fishingFritz()),
            Console::EAlignment::eCenter);
        Console::br();
        Console::printLn("dish of the day:", Console::EAlignment::eCenter);
        Console::printLn(std::format("~ {} ~", _dishOfTheDay), Console::EAlignment::eCenter);
        Console::br();

        CMenu menu;

        if (CGameManagement::getPlayerInstance()->gold() >= priceOfTheDay())
        {
            menu.addMenuGroup({menu.createAction(std::format("Eat dish of the day ({} Gold)", priceOfTheDay()), 'E')});
        }
        else
        {
            Console::printLn(
                std::format("The price for the dish of the day is: {} Gold. You are sure, that it is woth the "
                            "prize, but you just cannot afford.",
                            priceOfTheDay()));
        }

        menu.addMenuGroup({}, {CMenu::exit()});

        input = menu.execute();
        if (input.key == 'e')
        {
            eat();
        }

    } while (input != CMenu::exit());
}

void CFishRestaurant::makeDishOfTheDay()
{
    _dishOfTheDayLevel = FishingVillageRessources::getRandomRarity(FishingVillageRessources::rodLevelCap,
                                                                   FishingVillageRessources::boatLevelCap);

    auto fish = FishingVillageRessources::getFish(_dishOfTheDayLevel);

    switch (Randomizer::getRandom(5))
    {
    case 0:
    default:
        _dishOfTheDay = std::format("steamed {}", fish);
    case 1:
        _dishOfTheDay = std::format("fried {}", fish);
    case 2:
        _dishOfTheDay = std::format("{} sashimi", fish);
    case 3:
        _dishOfTheDay = std::format("{} bouillabaisse", fish);
    case 4:
        _dishOfTheDay = std::format("grilled {} filet", fish);
    }
}

unsigned int CFishRestaurant::priceOfTheDay() const
{
    return FishingVillageRessources::getFishPrice(_dishOfTheDayLevel) * 2;
}

void CFishRestaurant::eat() const
{
    Console::printLn("You get a plate with a steaming hot fish meal, and it tastes amazing!");
    CGameManagement::getPlayerInstance()->addGold(priceOfTheDay() * -1);

    switch (_dishOfTheDayLevel)
    {
    case FishingVillageRessources::EFishLevel::eCommon:
    default:
        CGameManagement::getPlayerInstance()->addHp(1);
        break;
    case FishingVillageRessources::EFishLevel::eUncommon:
        CGameManagement::getPlayerInstance()->addHp(2 + Randomizer::getRandom(2));
        break;
    case FishingVillageRessources::EFishLevel::eRare:
        CGameManagement::getPlayerInstance()->addHp(3 + Randomizer::getRandom(3));
        break;
    case FishingVillageRessources::EFishLevel::eUltraRare:
        CGameManagement::getPlayerInstance()->addHp(5 + Randomizer::getRandom(5));
        break;
    case FishingVillageRessources::EFishLevel::eLegend:
        CGameManagement::getPlayerInstance()->fullHeal();
        Console::printLn("This meal is a mind blowing experience");
        CGameManagement::getPlayerInstance()->levelUp();
        break;
    }
}
