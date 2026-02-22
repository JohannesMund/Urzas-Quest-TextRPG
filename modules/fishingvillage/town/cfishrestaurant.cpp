#include "cfishrestaurant.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "fishingvillage/moduleressources.h"
#include "randomizer.h"

#include <vector>

CFishRestaurant::CFishRestaurant() : CTownModule(TagNames::FishingVille::fishRestaurant)
{
}

void CFishRestaurant::execute()
{
    makeDishOfTheDay();

    CMenuAction input;

    do
    {
        Console::cls();

        Console::printLn(tr("{}'s Inn", FishingVillage::fishingVilleName()), Console::EAlignment::eCenter);
        Console::printLn(tr("Serving the best fresh fish since 833 ad. dragonis", Ressources::Game::fishingFritz()),
                         Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(tr("Dish of the day:"), Console::EAlignment::eCenter);
        Console::printLn(std::format("~ {} ~", _dishOfTheDay), Console::EAlignment::eCenter);
        Console::br();

        CMenu menu(FishingVillageMakeRod::moduleName());
        CMenuAction dishOfTheDayAction;

        if (CGameManagement::getPlayerInstance()->gold() >= priceOfTheDay())
        {
            dishOfTheDayAction = menu.createShopAction({"Eat dish of the day", 'E'}, priceOfTheDay());
            menu.addMenuGroup({dishOfTheDayAction});
        }
        else
        {
            Console::printLn(tr("The price for the dish of the day is: {} Gold. You are sure, that it is woth the "
                                "prize, but you just cannot afford.",
                                priceOfTheDay()));
        }

        menu.addMenuGroup({}, {CMenu::exit()});

        input = menu.execute();
        if (input == dishOfTheDayAction)
        {
            eat();
        }

    } while (input != CMenu::exit());
}

CMenuAction CFishRestaurant::townModuleNav(CMenu& menu) const
{
    return menu.createAction({"Restaurant", 'R'});
}

std::string CFishRestaurant::translatorModuleName() const
{
    return FishingVillageFishLegend::moduleName();
}

std::string CFishRestaurant::translatorObjectName() const
{
    return std::string(TagNames::FishingVille::fishRestaurant);
}

void CFishRestaurant::makeDishOfTheDay()
{
    _dishOfTheDayLevel = FishingVillage::getRandomRarity(FishingVillage::rodLevelCap, FishingVillage::boatLevelCap);

    auto fish = FishingVillage::getFish(_dishOfTheDayLevel);

    switch (Randomizer::getRandom(5))
    {
    case 0:
    default:
        _dishOfTheDay = tr("steamed {}", fish);
    case 1:
        _dishOfTheDay = tr("fried {}", fish);
    case 2:
        _dishOfTheDay = tr("{} sashimi", fish);
    case 3:
        _dishOfTheDay = tr("{} bouillabaisse", fish);
    case 4:
        _dishOfTheDay = tr("grilled {} filet", fish);
    }
}

int CFishRestaurant::priceOfTheDay() const
{
    return FishingVillage::getFishPrice(_dishOfTheDayLevel) * 2;
}

void CFishRestaurant::eat() const
{
    Console::printLn(tr("You get a plate with a steaming hot fish meal, and it tastes amazing!"));
    CGameManagement::getPlayerInstance()->spendGold(priceOfTheDay());

    switch (_dishOfTheDayLevel)
    {
    case FishingVillage::EFishLevel::eCommon:
    default:
        CGameManagement::getPlayerInstance()->addHp(1);
        break;
    case FishingVillage::EFishLevel::eUncommon:
        CGameManagement::getPlayerInstance()->addHp(2 + Randomizer::getRandom(2));
        break;
    case FishingVillage::EFishLevel::eRare:
        CGameManagement::getPlayerInstance()->addHp(3 + Randomizer::getRandom(3));
        break;
    case FishingVillage::EFishLevel::eUltraRare:
        CGameManagement::getPlayerInstance()->addHp(5 + Randomizer::getRandom(5));
        break;
    case FishingVillage::EFishLevel::eLegend:
        CGameManagement::getPlayerInstance()->fullHeal();
        Console::printLn(tr("This meal is a mind blowing experience"));
        CGameManagement::getPlayerInstance()->levelUp();
        break;
    }
}
