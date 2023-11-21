#include "cequipmentdealer.h"
#include "cgamemanagement.h"
#include "citemfactory.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"

#include <format>

CEquipmentDealer::CEquipmentDealer()
{
    _isSingleExecution = false;
    _type = CEncounter::eField;
}

void CEquipmentDealer::execute(const std::string_view& moduleName)
{
    CEncounter::execute();
    _hasBeenExecuted = true;

    Console::printLn(std::format(
        "Walking through some woods, you hear a whisper from behind a tree: {0}\"Hey, you!\"{1} you look in the "
        "direction of the voice and ask \"What me?\" the whispering voice replys: {0}\"Pscht! Yeah, you, "
        "exactly! Want to buy something? I have a great offer, exactly for you!\"{1}",
        CC::fgDarkGray(),
        CC::ccReset()));
    Console::printLn("This sounds totally trustworthy. Do you want to see what he has to offer?");
    Console::br();

    if (CMenu::executeAcceptRejectMenu() == CMenu::reject())
    {
        Console::printLn(
            "Well... A shaday dealer in the middle of nowhere. You might not be the brightest of them all, but...");
        return;
    }

    Console::printLn("Well... A shaday dealer in the middle of nowhere. What could possibly go wrong?");
    Console::printLn(
        std::format("You follow the whispering voice and find the {}shady {}dealer{} and look through offers.",
                    CC::fgLightGray(),
                    CC::fgDarkGray(),
                    CC::ccReset()));
    Console::br();

    std::vector<CItem*> buyableItems;
    for (int i = 0; i < 3; i++)
    {
        auto item =
            CGameManagement::getItemFactoryInstance()->makeShopEquipment(CGameManagement::getPlayerInstance()->level());

        if (item->buyValue() <= CGameManagement::getPlayerInstance()->gold())
        {
            buyableItems.push_back(item);
            Console::printLn(std::format("[{:3}] {} ({} Gold)", buyableItems.size(), item->name(), item->buyValue()));
        }
        else
        {
            Console::printLn(std::format("[   ] {} ({} Gold)", item->name(), item->buyValue()));
        }
    }

    Console::br();

    if (buyableItems.size())
    {
        auto input = Console::getNumberInputWithEcho(1, buyableItems.size());
        if (input.has_value())
        {
            auto item = buyableItems.at(*input - 1);
            CGameManagement::getInventoryInstance()->addItem(item);
            CGameManagement::getPlayerInstance()->addGold(item->buyValue() * -1);

            auto newEnd = std::remove(buyableItems.begin(), buyableItems.end(), item);
            if (newEnd != buyableItems.end())
            {
                buyableItems.erase(newEnd, buyableItems.end());
            }
        }
    }
    else
    {
        Console::printLn("Looks like, you cannot afford anything, this guy has to offer");
    }

    for (auto i : buyableItems)
    {
        delete i;
    }
}

unsigned int CEquipmentDealer::encounterChance(const EEncounterType& tp, const std::string_view& moduleName) const
{
    return 2;
}

std::string CEquipmentDealer::name() const
{
    return "Shady Dealer";
}

bool CEquipmentDealer::canBeExecuted(const EEncounterType& tp) const
{
    if (CGameManagement::getPlayerInstance()->level() < 5)
    {
        return false;
    }
    return CEncounter::canBeExecuted(tp);
}
