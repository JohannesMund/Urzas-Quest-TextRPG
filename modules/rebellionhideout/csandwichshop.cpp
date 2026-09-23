#include "csandwichshop.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "csandwich.h"
#include "csavefile.h"
#include "cshaggyssandwich.h"
#include "items/cbagofingredients.h"
#include "moduleressources.h"

#include <format>
#include <ranges>

CSandwichShop::CSandwichShop() : CRoom(TagNames::RebellionHideout::rebellionHideout)
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
    if (CGameManagement::now() - _turns > CGameManagement::getGameSettingsInstance()->turnsUntilShopRefresh())
    {
        replaceSandwichOfTheDay();
    }

    CMenuAction input;
    do
    {
        printHeader();
        checkForSoldSandwiches();
        checkForShaggysSandwich();
        showSandwichOfTheDay();

        CMenu menu(RebellionHideout::moduleName());

        auto makeAction = menu.createAction({"Make a sandwich", 'M'});
        auto deliverAction = menu.createAction({"Deliver ingredients", 'D'});
        auto observeAction = menu.createAction({"Observe, who buys your sandwiches", 'O'});
        auto revolutionaryAction = menu.createAction({"View revolutionary thoughts", 'V'});
        auto eatAction = menu.createShopAction({"Eat Sandwich of the Day"}, _sandwiches.at(0)->buyValue());

        auto rebellionAction = _hideout.townModuleNav(menu);

        CMenu::ActionList actions;

        if (_playerOwnsShop)
        {
            if (_sandwiches.size() < 5)
            {
                actions.push_back(makeAction);
            }
            if (CGameManagement::getInventoryInstance()->hasItem(CBagOfIngredients::CBagOfIngredientsFilter()))
            {
                actions.push_back(deliverAction);
            }

            if (seenRebellionHideoutHint())
            {
                actions.push_back(observeAction);
            }

            if (_playerDiscoveredHideout)
            {
                actions.push_back(rebellionAction);
            }
            else
            {
                actions.push_back(revolutionaryAction);
            }
        }
        else
        {
            if (CGameManagement::getPlayerInstance()->gold() >= _sandwiches.at(0)->buyValue())
            {
                actions.push_back(eatAction);
            }
            actions.push_back(revolutionaryAction);
        }

        menu.addMenuGroup(actions, {CMenu::exit()});

        input = menu.execute();
        if (input == eatAction)
        {
            eatSandwichOfTheDay();
        }
        if (input == makeAction)
        {
            makeASandwich();
        }
        if (input == deliverAction)
        {
            deliverIngredients();
        }
        if (input == observeAction)
        {
            observe();
        }
        if (input == rebellionAction)
        {
            _hideout.execute();
        }
        if (input == revolutionaryAction)
        {
            revolutionaryThoughts();
        }

    } while (input != CMenu::exit());
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

std::string CSandwichShop::translatorModuleName() const
{
    return RebellionHideout::moduleName();
}

nlohmann::json CSandwichShop::save() const
{
    nlohmann::json o = CRoom::save();
    o[TagNames::RebellionHideout::turns] = _turns;
    o[TagNames::RebellionHideout::playerOwnsShot] = _playerOwnsShop;
    o[TagNames::RebellionHideout::playerDiscoveredHideout] = _playerDiscoveredHideout;
    o[TagNames::RebellionHideout::gold] = _goldAvailable;

    nlohmann::json ingredients = nlohmann::json::array();
    for (auto i : _ingredientStore)
    {
        ingredients.push_back(
            {{TagNames::RebellionHideout::ingredient, i.first}, {TagNames::RebellionHideout::count, i.second}});
    }
    o[TagNames::RebellionHideout::ingredientStore] = ingredients;

    nlohmann::json sandwiches = nlohmann::json::array();
    for (auto s : _sandwiches)
    {
        CSaveFile::addGameObject(sandwiches, s);
    }
    o[TagNames::RebellionHideout::itemGeneratorsRegistered] = _itemGeneratorsRegistered;
    o[TagNames::RebellionHideout::rebellionHideout] = _hideout.save();

    return o;
}

void CSandwichShop::load(const nlohmann::json& json)
{
    CRoom::load(json);
    _turns = json.value<unsigned long>(TagNames::RebellionHideout::turns, 0);
    _goldAvailable = json.value<int>(TagNames::RebellionHideout::gold, 0);
    _playerOwnsShop = json.value<bool>(TagNames::RebellionHideout::playerOwnsShot, 0);
    _playerDiscoveredHideout = json.value<bool>(TagNames::RebellionHideout::playerDiscoveredHideout, false);

    if (json.contains(TagNames::RebellionHideout::ingredientStore))
    {
        for (auto i : json[TagNames::RebellionHideout::ingredientStore])
        {
            _ingredientStore.insert(std::make_pair(
                static_cast<CSandwich::EIngredients>(i.value<int>(TagNames::RebellionHideout::ingredient, 0)),
                i.value<int>(TagNames::RebellionHideout::count, 1)));
        }
    }

    _itemGeneratorsRegistered = json.value<bool>(TagNames::RebellionHideout::itemGeneratorsRegistered, false);
    if (_itemGeneratorsRegistered)
    {
        registerItemGenerators();
    }

    _hideout.load(json[TagNames::RebellionHideout::rebellionHideout]);
}

void CSandwichShop::printHeader()
{
    Console::cls();
    Console::printLn(std::format("{}", SandwichShop::sandwichShopName()), Console::EAlignment::eCenter);
    Console::printLn(tr("Ye olde Sandwich Shoppe, est. 489 ad. dragonis"), Console::EAlignment::eCenter);
    Console::br();

    if (!_playerOwnsShop)
    {
        Console::printLn(
            tr("The Sandwich shop is run by {}, an old man with a dream, who once started this shop "
               "to make the perfect sandwich, but after years and years of making and selling "
               "sandwiches lost all of his spirits. His sandwiches are still great though, but he reduced the "
               "menu to one single sandwich of the day, written on the sign next to the counter",
               SandwichShop::mrSoop()));
    }
    else
    {
        Console::printLn(tr("Here you are, your very own sandwich shop."));
    }

    if (!_playerDiscoveredHideout)
    {
        Console::printLn(
            tr("On one of the walls, you can see a blackboard. This board does not contain the menu, as one "
               "would expect, but a collection of hand written notes and pamphlets. A big headline tells you, "
               "what can be found there, it reads. \"Revolutionary Thoughts\""));
    }

    Console::br();
}

void CSandwichShop::showSandwichOfTheDay()
{
    Console::printLn(tr("Sandwiche{} of the day:", _sandwiches.size() == 0 ? "" : "s"), Console::EAlignment::eCenter);
    Console::br();

    if (_sandwiches.size() == 0)
    {
        Console::printLn(tr("SOLD OUT"), Console::EAlignment::eCenter);
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
}

void CSandwichShop::eatSandwichOfTheDay()
{
    _sandwiches.at(0)->useFromInventory();
    CGameManagement::getPlayerInstance()->spendGold(_sandwiches.at(0)->buyValue());
    replaceSandwichOfTheDay();
    Console::confirmToContinue();
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

        Console::printLn(tr(
            "As soon as you enter, you realize, that {0} acts stange, he snoops around your bag, he seems nervous and "
            "shakey. Eventually, he grabs into your bag and picks {1}. His eyes start to sparkle. \"This is it, this "
            "is {1}, the legendary sandwich, the perfect sandwich. I searched for this my whole life, no i finally "
            "found it! The only reason, i opened this sandwich shop was to find this sandwich!\" {0} literally has "
            "little hearts in his eyes, when i takes your {1} and runs to the exit. \"Ever wanted to own a Sandwich "
            "shop?\" he asks you before he leaves. \"its yours!\" are the last words  you hear from him. Guess, you "
            "are proud owner of a sandwich shop now.",
            SandwichShop::mrSoop(),
            sandwich));
        Console::confirmToContinue();

        _playerOwnsShop = true;
        CGameManagement::getInventoryInstance()->removeItem(CShaggysSandwich::shaggysSandwichFilter());
        CGameManagement::getProgressionInstance()->reportModuleFinished(SandwichShop::moduleName());
        CGameManagement::getProgressionInstance()->registerModuleHint(
            RebellionHideout::moduleName(),
            tr("You want to know where {} and {} are hiding? Are you really that blind? Did you ever woner "
               "who is buying you crappy sandwiches?",
               Ressources::Game::fiego(),
               Ressources::Game::brock()));
        registerItemGenerators();
    }
}

void CSandwichShop::checkForSoldSandwiches()
{
    if (_goldAvailable > 0)
    {
        Console::printLn(tr("While you were away, sandwiches have been sold and you earned {}{} Gold{}. This always "
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
}

bool CSandwichShop::seenRebellionHideoutHint()
{
    if (_playerDiscoveredHideout)
    {
        return false;
    }

    return CGameManagement::getProgressionInstance()->areModuleHintsSeen(RebellionHideout::moduleName());
}

void CSandwichShop::revolutionaryThoughts()
{
    Console::cls();
    Console::printLn(tr("The board is full of various notes with random thoughts, pieces of information or just rants "
                        "against the king. The sense for revolution seems to be strong in this land."));

    if (CGameManagement::getProgressionInstance()->areModuleQuestsAvailable())
    {
        auto quest = CGameManagement::getProgressionInstance()->getRandomQuest();

        Console::printLn(tr("On note catches your attention:"));
        Console::br();
        Console::printLn(quest.questText, Console::EAlignment::eCenter);
        Console::br();
        Console::printLn(tr("Do you accept this task?"));
        Console::br();
        if (CMenu::executeAcceptRejectMenu() == CMenu::accept())
        {
            Console::br();
            Console::printLn(
                tr("For the well-being of the land! For the rebellion! For {}! You accept the task, and leave.",
                   Ressources::Game::princessLeila()));
            CGameManagement::getProgressionInstance()->acceptModuleQuest(quest.moduleName);
        }
        else
        {
            Console::br();
            Console::printLn(
                tr("Revolution is not exactly your cup of ale, so you decide to leave the revolution for the "
                   "revolutionaries."));
        }
    }
    else
    {
        Console::printLn(tr("But even after several closer looks, you cannot find anything of interest there."));
    }
    Console::br();
    Console::confirmToContinue();
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

        Console::printLn(tr("You open a {} and put {} into your stroage.",
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
        Console::printLn(tr("You have no ingredients available to make a sandwich"));
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
        Console::printLn(tr("Make a sandwich"), Console::EAlignment::eCenter);
        Console::br();
        if (ingredients.size() > 0)
        {
            Console::printLn(tr("Selected Ingredients: {}", CSandwich::ingredients2String(ingredients)));
        }

        CSandwich::IngredientsList availableIngredients;

        for (auto i : _ingredientStore | std::views::filter([](const auto& p) { return p.second > 0; }) |
                          std::views::transform([](const auto& p) { return p.first; }))
        {
            availableIngredients.push_back(i);
            Console::printLn(std::format("[{:3}] {}", availableIngredients.size(), CSandwich::ingredient2String(i)));
        }

        input = Console::getNumberInputWithEcho(1, availableIngredients.size());

        if (input.has_value())
        {
            auto ingredient = availableIngredients.at((*input) - 1);
            ingredients.push_back(ingredient);
            _ingredientStore.at(ingredient)--;
        }
    } while (input.has_value() && countIngredients() > 0);

    _sandwiches.push_back(new CSandwich(ingredients));
}

void CSandwichShop::observe()
{
    Console::cls();
    _playerDiscoveredHideout = true;
    CGameManagement::getProgressionInstance()->unregisterModuleHintsByModuleName(RebellionHideout::moduleName());
    CGameManagement::getProgressionInstance()->reportModuleFinished(RebellionHideout::moduleName());

    Console::printLn(
        tr("You decide, to hide in your sandwich shop, and see, who is buying you sandwiches. As soon as the "
           "sun sets, you hear a rumbling, coming from the employees bathroom (you wonder, why this sandwich "
           "shop even has an employees bathroom, you have no employees), but the toilet is pushed aside, and "
           "two guys appear. They seem to be hungry, and immediately rush to the sandwiches."));
    Console::printLn(tr("They put the money into the money box and start eating. \"The new guy really makes awesomne "
                        "sandwiches\" - \"Yeah, so much better than {}, this guy really is a sandwich legend.\"",
                        SandwichShop::mrSoop()));
    Console::br();
    Console::printLn(
        tr("A little bit proud, that they call you a sandwich legend, you leave your hideout. \"Who are you "
           "two, and why are you hiding in my sandwich store?\""));
    Console::printLn(tr("A little bit shocked, the two guys stop eating and introduce themselves. \"My name is {} and "
                        "this is {}\" says the first guy \"We are the leaders of the rebellion\", says the other.",
                        Ressources::Game::fiego(),
                        Ressources::Game::brock()));
    Console::printLn(tr("\"Sou you are the guys who kidnapped {0} repeatedly?\" you ask. \"So you are the one, who "
                        "intercepted our plans to abduct {0} repeatedly?\" answer the two rebellion leaders.",
                        Ressources::Game::princessLeila()));
    Console::printLn(
        tr("After some laughing, you decide to work together. You provide them with food and support, they "
           "will not abduct any princess, without your approval."));
    Console::confirmToContinue();

    Console::printLn(
        tr("The rest of the night is spent, talking about the rebellion. Both, {0} and {1} think, that {2} is "
           "more a clown, than a king, and after you saw {2}, you agree with the. They also seem to know a "
           "lot more about {3}, but they always put you of to \"another time\" as soon as {3} is mentioned.",
           Ressources::Game::fiego(),
           Ressources::Game::brock(),
           Ressources::Game::kingJesster(),
           Ressources::Game::urza()));
    Console::printLn(
        tr("You are also very surprised to hear, that the {} you saw at the beginning of your adventure is actually a "
           "minion of {}, who travels through the land, making propaganda for the king and against the {} - cults.",
           Ressources::Game::dancingBard(),
           Ressources::Game::kingJesster(),
           Ressources::Game::urza()));
    Console::br();
    Console::printLn(
        tr("Funny story: {} and {} where part of the rebellion too, but had to leave, because their constant "
           "crying did not add anything to the whole deal. \"You met them?\" {} asks you surprised. \"How are "
           "they?\" - \"Well, at least this time, they stopped crying for once\", you answer, making clear, "
           "that you will not carry that topic out any more.",
           Ressources::Game::bimmelchen(),
           Ressources::Game::pimmelchen(),
           Ressources::Game::fiego()));
    Console::br();
    Console::printLn(tr("{} and {} look at you, stunned.", Ressources::Game::fiego(), Ressources::Game::brock()));
    Console::confirmToContinue();
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
    _turns = CGameManagement::now();
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

void CSandwichShop::registerItemGenerators()
{
    CGameManagement::getItemFactoryInstance()->registerShopItemGenerator(
        SandwichShop::moduleName(), &CBagOfIngredients::makeShopItem, 10);
    CGameManagement::getItemFactoryInstance()->registerLootItemGenerator(
        SandwichShop::moduleName(), &CBagOfIngredients::makeLootItem, 10);
    _itemGeneratorsRegistered = true;
}
