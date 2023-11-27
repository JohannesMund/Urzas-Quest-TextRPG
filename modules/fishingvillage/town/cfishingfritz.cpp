#include "cfishingfritz.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "fishingvillage/items/cboat.h"
#include "fishingvillage/items/cboatpart.h"
#include "fishingvillage/items/cfish.h"
#include "fishingvillage/items/cfishingrod.h"
#include "fishingvillage/items/cfishingrodpart.h"
#include "fishingvillage/moduleressources.h"

#include <format>

CFishingFritz::CFishingFritz()
{
}

void CFishingFritz::execute()
{
    CMenu::Action input;

    do
    {
        printHeader();

        CMenu menu;

        CMenu::ActionList moduleActionList;
        CMenu::ActionList defaultActionList;

        if (!isOpen())
        {
            Console::printLn(
                std::format("{}'s fishing shop is an old, ramshackle hut. It is good, that the weather here is always "
                            "sunny and clear, because this hut would probably collapse, when hit by a medium strong "
                            "wind. Also, it will offer not much protection against rain, snow, or even cold.",
                            Ressources::Game::fishingFritz()));
            Console::printLn("There is a sign on the locked door reding:");
            Console::printLn("\"Gone fishing, come back later\"", Console::EAlignment::eCenter);
        }
        else
        {
            if (hasFish())
            {
                defaultActionList.push_back(menu.createAction(sellYourFish(), 'S'));
            }

            if (CGameManagement::getProgressionInstance()->isModuleActive(
                    FishingVillageRessources::moduleNameFishLegend()) ||
                CGameManagement::getProgressionInstance()->isModuleFinished(
                    FishingVillageRessources ::moduleNameFishLegend()))
            {
                defaultActionList.push_back(menu.createAction("Ask for Information", 'A'));
            }

            defaultActionList.push_back(menu.createAction("Enhance Equipment", 'E'));
        }

        menu.addMenuGroup(moduleActionList);
        menu.addMenuGroup(defaultActionList, {CMenu::exit()});
        input = menu.execute();

        if (input.key == 'a')
        {
            ask();
        }
        if (input.key == 's')
        {
            sell();
        }
        if (input.key == 'e')
        {
            enhance();
        }

    } while (input != CMenu::exit());
}

void CFishingFritz::printHeader() const
{
    Console::cls();
    Console::printLn(std::format("{}", Ressources::Game::fishingFritz()), Console::EAlignment::eCenter);
    Console::printLn(std::format("Fishing fresh fish since 832 ad. dragonis", Ressources::Game::fishingFritz()),
                     Console::EAlignment::eCenter);
    Console::br();
}

bool CFishingFritz::isOpen() const
{
    return CGameManagement::getProgressionInstance()->isModuleActive(FishingVillageRessources::moduleNameMakeRod()) ||
           CGameManagement::getProgressionInstance()->isModuleFinished(FishingVillageRessources::moduleNameMakeRod());
}

void CFishingFritz::ask()
{
    if (CGameManagement::getProgressionInstance()->isModuleFinished(FishingVillageRessources::moduleNameFishLegend()))
    {
        getInformation();
    }
    else
    {
        checkFish();
    }
}

void CFishingFritz::checkFish()
{
    if (_firstVisit)
    {
        _firstVisit = false;
        Console::printLn(
            std::format("Straight to the point, you ask {} about everything: {}, {}, {}, you even show him you {} "
                        "tattoo. You just make clear, that you need to know everything, no matter the cost.",
                        Ressources::Game::fishingFritz(),
                        Ressources::Game::urza(),
                        Ressources::Game::fiego(),
                        Ressources::Game::brock(),
                        Ressources::Game::princessLayla()));
        Console::printLn(std::format(
            "{} looks at you suspicious and tells you, that he knows a lot, but not, wether he can trust you. the only "
            "people he can trust, are prople who are able to bring him {}. The legendary fish that can be caught in {}",
            Ressources::Game::fishingFritz(),
            FishingVillageRessources::getFish(FishingVillageRessources::EFishLevel::eLegend),
            FishingVillageRessources::fishingVilleName()));
        Console::printLn("looks, as if you have another task.");
        Console::confirmToContinue();
        return;
    }

    if (CGameManagement::getInventoryInstance()->hasItem(
            CFish::fishRarityFilter(FishingVillageRessources::EFishLevel::eLegend)))
    {
        Console::printLn(std::format("{} Smiles at you. Well he smiles more at the {} than he smiles at you. But at "
                                     "least he smiles for the first time since... For the first time.",
                                     Ressources::Game::fishingFritz(),
                                     FishingVillageRessources::getFish(FishingVillageRessources::EFishLevel::eLegend)));
        Console::printLn(
            "Of course, he cannot pay you for the fish, but at least he is willing to give you information.");
        Console::printLn(std::format("{0} is a legend. But {1} and {2} are heroes, and they surely can tell you more "
                                     "about {0}. To find them, you should find {3}.",
                                     Ressources::Game::urza(),
                                     Ressources::Game::fiego(),
                                     Ressources::Game::brock(),
                                     Ressources::Game::mobi()));
        Console::printLn(std::format("This adds another name to your list. How... frustrating, but maybe, this {} is "
                                     "easier to find that the other guys. You will find out.",
                                     Ressources::Game::mobi()));

        CGameManagement::getProgressionInstance()->reportModuleFinished(
            FishingVillageRessources::moduleNameFishLegend());
    }
    else
    {
        Console::printLn(
            std::format("{} looks grumpy at you and shakes his head. No fish, no information. A deal is a deal.",
                        Ressources::Game::fishingFritz()));
        Console::printLn(std::format("How hard can it be to catch a {}?",
                                     FishingVillageRessources::getFish(FishingVillageRessources::EFishLevel::eLegend)));
    }
    Console::confirmToContinue();
}

void CFishingFritz::getInformation() const
{
    CMenu menu;
    CMenu::ActionList actions;
    auto hint = CGameManagement::getProgressionInstance()->getRandomHint();

    if (hint.empty())
    {
        Console::printLn(std::format("{} thinks, but finally shakes his head. \"My informants have nothing right "
                                     "now.\". Seems like you will have to come back later.",
                                     Ressources::Game::fishingFritz()));
    }
    else
    {
        Console::printLn(
            std::format("{} looks at you conspirational. \"Indeed, I have new information for you. But this "
                        "information is explosive! So explosive, that one of my informants died, delivering ist. you "
                        "will understand, that i will have to charge you something to get it. It will cost you {}{} "
                        "Gold{} to get this information.\"",
                        Ressources::Game::fishingFritz(),
                        CC::fgLightYellow(),
                        Ressources::Config::informationCost,
                        CC::ccReset()));

        if (CGameManagement::getPlayerInstance()->gold() > Ressources::Config::informationCost)
        {
            actions.push_back(
                menu.createAction(std::format("Get information ({} Gold)", Ressources::Config::informationCost), 'G'));
        }
        else
        {
            Console::br();
            Console::printLn("This seems to be a high price for some piece of information, so you reject.");
        }
    }

    menu.addMenuGroup(actions, {CMenu::exit()});
    if (menu.execute().key == 'g')
    {
        CGameManagement::getPlayerInstance()->spendGold(Ressources::Config::informationCost);
        Console::printLn(std::format("{} closes the door, and gives you the hottst information he has available:",
                                     Ressources::Game::fishingFritz()));
        Console::br();
        Console::printLn(hint, Console::EAlignment::eCenter);
        Console::br();
        Console::confirmToContinue();
    }
}
void CFishingFritz::sell() const
{
    auto items = CGameManagement::getInventoryInstance()->getItemsByFilter(CFish::fishFilter());
    if (items.size() == 0)
    {
        return;
    };
    for (const auto& item : items)
    {
        CGameManagement::getPlayerInstance()->gainGold(item->value());
        CGameManagement::getInventoryInstance()->removeItem(item);
    }
    Console::confirmToContinue();
}

void CFishingFritz::enhance() const
{
    auto items = CGameManagement::getInventoryInstance()->getEnhancableEquipment();
    CInventory::EnhancableEquipmentList enhancableItems;

    auto checkAndPrint = [&enhancableItems](CEquipment* item)
    {
        if (item == nullptr)
        {
            return;
        }
        auto cost = item->upgradeCost();

        if (cost <= CGameManagement::getPlayerInstance()->gold())
        {
            enhancableItems.push_back(item);
            Console::printLn(std::format("[{:3}] {} ({} Gold)", enhancableItems.size(), item->name(), cost));
        }
        else
        {
            Console::printLn(std::format("[   ] {} ({} Gold)", item->name(), cost));
        }
    };

    for (auto& item : items)
    {
        checkAndPrint(dynamic_cast<CFishingRod*>(item));
        checkAndPrint(dynamic_cast<CBoat*>(item));
    }

    if (enhancableItems.size() > 0)
    {
        auto idx = Console::getNumberInputWithEcho(1, enhancableItems.size());
        if (idx.has_value())
        {
            auto item = enhancableItems.at(*idx - 1);
            auto cost = item->upgradeCost();
            item->enhance();
            CGameManagement::getPlayerInstance()->spendGold(cost);
        }
    }
    Console::confirmToContinue();
}

bool CFishingFritz::isMakeRodActive() const
{
    return CGameManagement::getProgressionInstance()->isModuleActive(FishingVillageRessources::moduleNameMakeRod());
}

bool CFishingFritz::isMakeBoatActive() const
{
    return CGameManagement::getProgressionInstance()->isModuleActive(FishingVillageRessources::moduleNameMakeBoat());
}

bool CFishingFritz::hasFish() const
{
    return CGameManagement::getInventoryInstance()->hasItem(CFish::fishFilter());
}

std::string CFishingFritz::sellYourFish() const
{
    auto items = CGameManagement::getInventoryInstance()->getItemsByFilter(CFish::fishFilter());
    if (items.size() == 0)
    {
        return "";
    }

    unsigned int value = 0U;
    for (const auto& item : items)
    {
        value += item->value();
    }

    return std::format("Sell your fish ({} Gold)", value);
}
