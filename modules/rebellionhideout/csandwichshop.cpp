#include "csandwichshop.h"
#include "cbagofingredients.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "csandwich.h"
#include "cshaggyssandwich.h"
#include "moduleressources.h"

#include <format>

CSandwichShop::CSandwichShop()
{
    for (const auto i : CSandwich::ingredientIterator())
    {
        _ingredientStore.insert(std::make_pair(i, 0));
    }

    replaceSandwichOfTheDay();

    _description = "";

    _encounterType = CEncounter::EEncounterType::eNone;
    _isRandomTaskPossible = true;
    _showInFogOfWar = false;
}

void CSandwichShop::execute()
{
    CRoom::execute();
    if (CGameManagement::getProgressionInstance()->turns() - _turns > Ressources::Config::turnsUntilShopRefresh)
    {
        replaceSandwichOfTheDay();
    }

    checkForShaggysSandwich();

    if (_playerOwnsShop)
    {
        sellSandwiches();
    }
    else
    {
        showSandwichOfTheDay();
    }
}

std::string CSandwichShop::bgColor() const
{
    return CC::bgGreen();
}

std::string CSandwichShop::fgColor() const
{
    return CC::fgLightYellow();
}

CMap::RoomFilter CSandwichShop::sandwichShopFilter()
{
    return [](const CRoom* room) { return dynamic_cast<const CSandwichShop*>(room) != nullptr; };
}

void CSandwichShop::printHeader()
{
    Console::cls();
    Console::printLn(std::format("{}", RebellionHideoutRessources::sandwichShopName()), Console::EAlignment::eCenter);
    Console::printLn("Ye olde Sandwich Shoppe, est. 489 ad. dragonis", Console::EAlignment::eCenter);
    Console::br();
}

void CSandwichShop::showSandwichOfTheDay()
{
    printHeader();
    Console::printLn(
        std::format("The Sandwich shop is run by {}, an old man with a dream, who once started this shop "
                    "to make the perfect sandwich, but after years and years of making and selling "
                    "sandwiches lost all of his spirits. His sandwiches are still great though, but he reduced the "
                    "menu to one single sandwich of the day, written on the sign next to the counter",
                    RebellionHideoutRessources::mrSoop()));
    Console::br();
    Console::printLn("Sandwich of the day:", Console::EAlignment::eCenter);
    Console::printLn(_sandwiches.at(0)->description(), Console::EAlignment::eCenter);
    Console::br();

    CMenu menu;

    if (CGameManagement::getPlayerInstance()->gold() >= _sandwiches.at(0)->buyValue())
    {
        menu.addMenuGroup(
            {menu.createAction(std::format("Eat Sandwich of the Day ({} Gold)", _sandwiches.at(0)->buyValue()), 'E')},
            {CMenu::exit()});
    }
    else
    {
        menu.addMenuGroup({}, {CMenu::exit()});
    }

    if (menu.execute().key == 'e')
    {
        eatSandwichOfTheDay();
    }
}

void CSandwichShop::eatSandwichOfTheDay()
{
    _sandwiches.at(0)->useFromInventory();
    CGameManagement::getPlayerInstance()->spendGold(_sandwiches.at(0)->buyValue());
    replaceSandwichOfTheDay();
}

void CSandwichShop::checkForShaggysSandwich()
{
    if (_playerOwnsShop)
    {
        return;
    }

    auto list = CGameManagement::getInventoryInstance()->getItemsByFilter(CShaggysSandwich::shaggysSandwichFilter());
    std::string sandwich;

    if (list.size() != 0)
    {
        sandwich = list.at(0)->name();

        Console::printLn(std::format(
            "As soon as you enter, you realize, that {0} acts stange, he snoops around your bag, he seems nervous and "
            "shakey. Eventually, he grabs into your bag and picks {1}. His eyes start to sparkle. \"This is it, this "
            "is {1}, the legendary sandwich, the perfect sandwich. I searched for this my whole life, no i finally "
            "found it! The only reason, i opened this sandwich shop was to find this sandwich!\" {0} literally has "
            "little hearts in his eyes, when i takes your {1} and runs to the exit. \"Ever wanted to own a Sandwich "
            "shop?\" he asks you before he leaves. \"its yours!\" are the last words  you hear from him. Guess, you "
            "are proud owner of a sandwich shop now.",
            RebellionHideoutRessources::mrSoop(),
            sandwich));
        Console::confirmToContinue();

        _playerOwnsShop = true;
        CGameManagement::getInventoryInstance()->removeItem(CShaggysSandwich::shaggysSandwichFilter());
        CGameManagement::getProgressionInstance()->registerModuleHint(
            RebellionHideoutRessources::moduleNameRebellionHideout(),
            std::format("You want to know where {} and {} are hiding? Are you really that blind? Did you ever woner "
                        "who is buying you crappy sandwiches?",
                        Ressources::Game::fiego(),
                        Ressources::Game::brock()));
    }
}

void CSandwichShop::deliverIngredients()
{
    auto bags = CGameManagement::getInventoryInstance()->getItemsByFilter(CBagOfIngredients::CBagOfIngredientsFilter());
    if (!bags.size())
    {
        return;
    }

    for (const auto& bag : bags)
    {
        auto ingredients = dynamic_cast<const CBagOfIngredients*>(bag)->getIngredients();

        Console::printLn(std::format("You open a {} and put {} into your stroage.",
                                     bag->name(),
                                     CBagOfIngredients::ingredients2String(ingredients)));
        Console::br();
        for (const auto& i : ingredients)
        {
            _ingredientStore.at(i)++;
        }
        CGameManagement::getInventoryInstance()->removeItem(bag);
    }
    Console::confirmToContinue();
}

void CSandwichShop::makeASandwich()
{
    if (countIngredients() <= 0)
    {
        Console::br();
        Console::printLn("You have no ingredients available to make a sandwich");
        Console::br();
        Console::confirmToContinue();
        return;
    }

    std::optional<int> input = {};
    CSandwich::IngredientsList ingredients;
    do
    {
        Console::cls();
        Console::br();
        Console::printLn("Make a sandwich", Console::EAlignment::eCenter);
        Console::br();
        if (ingredients.size() > 0)
        {
            Console::printLn(std::format("Selected Ingredients: {}", CSandwich::ingredients2String(ingredients)));
        }

        CSandwich::IngredientsList availableIngredients;

        int index = 0;

        for (auto i : CSandwich::ingredientIterator())
        {
            if (_ingredientStore.at(i) <= 0)
            {
                continue;
            }

            index++;
            Console::printLn(std::format("[{:3}] {}", index, CSandwich::ingredient2String(i)));
            availableIngredients.push_back(i);
        }

        input = Console::getNumberInputWithEcho(index - 1);

        if (input.has_value())
        {
            auto ingredient = availableIngredients.at((*input) - 1);
            ingredients.push_back(ingredient);
            _ingredientStore.at(ingredient)--;
        }
    } while (input.has_value() && countIngredients() > 0);

    _sandwiches.push_back(new CSandwich(ingredients));
}

void CSandwichShop::sellSandwiches()
{
    CMenu::Action input;
    do
    {
        Console::cls();
        printHeader();

        Console::printLn("Sandwiches of the day:", Console::EAlignment::eCenter);
        Console::br();

        if (_sandwiches.size() == 0)
        {
            Console::printLn("SOLD OUT", Console::EAlignment::eCenter);
            Console::br();
        }
        else
        {
            for (auto s : _sandwiches)
            {
                Console::printLn(s->description(), Console::EAlignment::eCenter);
                Console::br();
            }
        }

        if (_goldAvailable > 0)
        {
            Console::printLn(
                std::format("While you were away, sandwiches have been sold and you earned {}{} Gold{}. This always "
                            "happens. You wonder who is selling the sandwiches, there seems to be no staff here. at "
                            "least you hired nobody. Even more you wonder who is buying your sandwiches, and who is "
                            "honest enough to pay, with no staff on duty. One day, you will have to check for that.",
                            CC::fgLightYellow(),
                            _goldAvailable,
                            CC::ccReset()));
            CGameManagement::getPlayerInstance()->gainGold(_goldAvailable);
            _goldAvailable = 0;
            Console::br();
        }

        CMenu menu;

        CMenu::ActionList actions;

        if (_sandwiches.size() < 5)
        {
            actions.push_back(menu.createAction("Make a sandwich", 'M'));
        }
        if (CGameManagement::getInventoryInstance()->hasItem(CBagOfIngredients::CBagOfIngredientsFilter()))
        {
            actions.push_back(menu.createAction("Deliver ingredients", 'D'));
        }

        menu.addMenuGroup(actions, {CMenu::exit()});
        input = menu.execute();

        if (input.key == 'm')
        {
            makeASandwich();
        }
        if (input.key == 'd')
        {
            deliverIngredients();
        }

    } while (input != CMenu::exit());
}

int CSandwichShop::countIngredients()
{
    int count = 0;
    for (const auto& i : _ingredientStore)
    {
        count += i.second;
    }
    return count;
}

char CSandwichShop::getMapSymbol() const
{
    return 'S';
}

void CSandwichShop::replaceSandwichOfTheDay()
{
    _turns = CGameManagement::getProgressionInstance()->turns();
    for (auto i : _sandwiches)
    {
        if (_playerOwnsShop)
        {
            _goldAvailable += i->buyValue();
        }

        delete i;
    }
    _sandwiches.clear();
    if (_playerOwnsShop == false)
    {
        _sandwiches.push_back(CGameManagement::getItemFactoryInstance()->sandwichMaker());
    }
}
