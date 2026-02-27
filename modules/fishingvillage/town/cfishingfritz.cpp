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

CFishingFritz::CFishingFritz() : CTownModule(TagNames::FishingVille::fishingFritz)
{
}

void CFishingFritz::execute()
{
    CMenuAction input;

    do
    {
        printHeader();

        CMenu menu(FishingVillageMakeRod::moduleName());

        CMenu::ActionList defaultActionList;
        CMenuAction sellAction;

        const auto val = fishValue();
        if (val > 0)
        {
            sellAction = menu.createShopAction({"Sell your fish", 'S'}, val);
        }

        CMenuAction askAction = menu.createAction({"Ask for Information", 'A'});
        CMenuAction enhanceAction = menu.createAction({"Enhance Equipment", 'E'});

        if (!isOpen())
        {
            Console::printLn(
                tr("{}'s fishing shop is an old, ramshackle hut. It is good, that the weather here is always "
                   "sunny and clear, because this hut would probably collapse, when hit by a medium strong "
                   "wind. Also, it will offer not much protection against rain, snow, or even cold.",
                   Ressources::Game::fishingFritz()));
            Console::printLn(tr("There is a sign on the locked door reading:"));
            Console::printLn(tr("\"Gone fishing, come back later\""), Console::EAlignment::eCenter);
        }
        else
        {
            if (hasFish())
            {
                defaultActionList.push_back(sellAction);
            }

            if (CGameManagement::getProgressionInstance()->isModuleActive(FishingVillageFishLegend::moduleName()) ||
                CGameManagement::getProgressionInstance()->isModuleFinished(FishingVillageFishLegend::moduleName()))
            {
                defaultActionList.push_back(askAction);
            }

            defaultActionList.push_back(enhanceAction);
        }

        menu.addMenuGroup(defaultActionList, {CMenu::exit()});
        input = menu.execute();

        if (input == askAction)
        {
            ask();
        }
        if (input == sellAction)
        {
            sell();
        }
        if (input == enhanceAction)
        {
            enhance();
        }
    } while (input != CMenu::exit());
}

CMenuAction CFishingFritz::townModuleNav(CMenu& menu) const
{
    return menu.createAction({CC::unColorizeString(Ressources::Game::fishingFritz()), 'f'});
}

nlohmann::json CFishingFritz::save() const
{
    nlohmann::json o;
    o["firstVisit"] = _firstVisit;
    return o;
}

void CFishingFritz::load(const nlohmann::json& o)
{
    _firstVisit = o["firstVisit"];
}

std::string CFishingFritz::translatorModuleName() const
{
    return FishingVillageFishLegend::moduleName();
}

std::string CFishingFritz::translatorObjectName() const
{
    return std::string(TagNames::FishingVille::fishingFritz);
}

void CFishingFritz::printHeader() const
{
    Console::cls();
    Console::printLn(std::format("{}", Ressources::Game::fishingFritz()), Console::EAlignment::eCenter);
    Console::printLn(tr("Fishing fresh fish since 832 ad. dragonis", Ressources::Game::fishingFritz()),
                     Console::EAlignment::eCenter);
    Console::br();
}

bool CFishingFritz::isOpen() const
{
    return CGameManagement::getProgressionInstance()->isModuleActive(FishingVillageMakeRod::moduleName()) ||
           CGameManagement::getProgressionInstance()->isModuleFinished(FishingVillageMakeRod::moduleName());
}

void CFishingFritz::ask()
{
    if (CGameManagement::getProgressionInstance()->isModuleFinished(FishingVillageFishLegend::moduleName()))
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
        Console::printLn(tr("Straight to the point, you ask {} about everything: {}, {}, {}, you even show him you {} "
                            "tattoo. You just make clear, that you need to know everything, no matter the cost.",
                            Ressources::Game::fishingFritz(),
                            Ressources::Game::urza(),
                            Ressources::Game::fiego(),
                            Ressources::Game::brock(),
                            Ressources::Game::princessLeila()));
        Console::printLn(tr(
            "{} looks at you suspicious and tells you, that he knows a lot, but not, wether he can trust you. the only "
            "people he can trust, are prople who are able to bring him {}. The legendary fish that can be caught in {}",
            Ressources::Game::fishingFritz(),
            FishingVillage::getFish(FishingVillage::EFishLevel::eLegend),
            FishingVillage::fishingVilleName()));
        Console::printLn(tr("looks, as if you have another task."));
        Console::confirmToContinue();
        return;
    }

    auto fish = CGameManagement::getInventoryInstance()->getFirstItemByFilter<CFish>(
        CFish::fishRarityFilter(FishingVillage::EFishLevel::eLegend));
    if (fish.has_value())
    {
        Console::printLn(tr("{} Smiles at you. Well he smiles more at the {} than he smiles at you. But at "
                            "least he smiles for the first time since... For the first time.",
                            Ressources::Game::fishingFritz(),
                            FishingVillage::getFish(FishingVillage::EFishLevel::eLegend)));
        Console::printLn(
            tr("Of course, he cannot pay you for the fish, but at least he is willing to give you information."));
        Console::printLn(tr("{0} is a legend. But {1} and {2} are heroes, and they surely can tell you more "
                            "about {0}. To find them, you should find {3}.",
                            Ressources::Game::urza(),
                            Ressources::Game::fiego(),
                            Ressources::Game::brock(),
                            Ressources::Game::darkMobi()));
        Console::printLn(tr("This adds another name to your list. How... frustrating, but maybe, this {} is "
                            "easier to find that the other guys. You will find out.",
                            Ressources::Game::darkMobi()));

        CGameManagement::getInventoryInstance()->removeItem(fish.value());
        CGameManagement::getProgressionInstance()->reportModuleFinished(FishingVillageFishLegend::moduleName());
    }
    else
    {
        Console::printLn(tr("{} looks grumpy at you and shakes his head. No fish, no information. A deal is a deal.",
                            Ressources::Game::fishingFritz()));
        Console::printLn(
            tr("How hard can it be to catch a {}?", FishingVillage::getFish(FishingVillage::EFishLevel::eLegend)));
    }
    Console::confirmToContinue();
}

void CFishingFritz::getInformation() const
{
    CMenu menu(FishingVillageMakeRod::moduleName());
    CMenu::ActionList actions;
    const auto informationCost = CGameManagement::getGameSettingsInstance()->informationCost();

    CMenuAction askAction;

    if (CGameManagement::getProgressionInstance()->moduleHintsAvailable())
    {
        Console::printLn(tr("{} thinks, but finally shakes his head. \"My informants have nothing right "
                            "now.\". Seems like you will have to come back later.",
                            Ressources::Game::fishingFritz()));
    }
    else
    {
        Console::printLn(
            tr("{} looks at you conspirational. \"Indeed, I have new information for you. But this "
               "information is explosive! So explosive, that one of my informants died, delivering ist. you "
               "will understand, that i will have to charge you something to get it. It will cost you {}{} "
               "Gold{} to get this information.\"",
               Ressources::Game::fishingFritz(),
               CC::fgLightYellow(),
               informationCost,
               CC::ccReset()));

        if (CGameManagement::getPlayerInstance()->gold() > informationCost)
        {
            askAction = menu.createShopAction({"Get information", 'G'}, informationCost);
            actions.push_back(askAction);
        }
        else
        {
            Console::br();
            Console::printLn(tr("This seems to be a high price for some piece of information, so you reject."));
        }
    }

    menu.addMenuGroup(actions, {CMenu::exit()});
    if (menu.execute() == askAction)
    {
        auto hint = CGameManagement::getProgressionInstance()->getRandomHint();
        CGameManagement::getPlayerInstance()->spendGold(informationCost);

        Console::printLn(tr("{} closes the door, and gives you the hottst information he has available:",
                            Ressources::Game::fishingFritz()));
        Console::br();
        Console::printLn(hint, Console::EAlignment::eCenter);
        Console::br();
        Console::confirmToContinue();
    }
}
void CFishingFritz::sell() const
{
    auto fishes = CGameManagement::getInventoryInstance()->getItemsByFilter(CFish::fishFilter());
    if (fishes.size() == 0)
    {
        return;
    };
    for (const auto& fish : fishes)
    {
        CGameManagement::getPlayerInstance()->gainGold(fish->value());
        CGameManagement::getInventoryInstance()->removeItem(fish);
    }
    Console::confirmToContinue();
}

void CFishingFritz::enhance() const
{
    auto items = CGameManagement::getInventoryInstance()->getEnhancableEquipment();
    CInventory::EnhancableEquipmentList enhancableItems;

    for (auto& item : items)
    {
        checkAndPrint(enhancableItems, dynamic_cast<CFishingRod*>(item));
        checkAndPrint(enhancableItems, dynamic_cast<CBoat*>(item));
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
    return CGameManagement::getProgressionInstance()->isModuleActive(FishingVillageMakeRod::moduleName());
}

bool CFishingFritz::isMakeBoatActive() const
{
    return CGameManagement::getProgressionInstance()->isModuleActive(FishingVillageMakeBoat::moduleName());
}

bool CFishingFritz::hasFish() const
{
    return CGameManagement::getInventoryInstance()->hasItem(CFish::fishFilter());
}

int CFishingFritz::fishValue() const
{
    auto items = CGameManagement::getInventoryInstance()->getItemsByFilter(CFish::fishFilter());
    if (items.size() == 0)
    {
        return 0;
    }

    unsigned int value = 0U;
    for (const auto& item : items)
    {
        value += item->value();
    }

    return value;
}

void CFishingFritz::checkAndPrint(CInventory::EnhancableEquipmentList& equipmentList, CEquipment* item) const
{
    if (item == nullptr)
    {
        return;
    }
    int cost = item->upgradeCost();

    if (cost <= CGameManagement::getPlayerInstance()->gold())
    {
        equipmentList.push_back(item);
        Console::printLn(tr("[{:3}] {} ({} Gold)", equipmentList.size(), item->name(), cost));
    }
    else
    {
        Console::printLn(tr("[   ] {} ({} Gold)", item->name(), cost));
    }
}
