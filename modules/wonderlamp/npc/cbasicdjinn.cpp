#include "cbasicdjinn.h"

#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"
#include "core.h"
#include "randomizer.h"
#include "wonderlamp/items/cgem.h"
#include "wonderlamp/moduleressources.h"

CBasicDjinn::CBasicDjinn(const Core::EGender gender) : CNpc(TagNames::WonderLamp::djinn, gender)
{
}

void CBasicDjinn::interact()
{
    CNpc::interact();
    CMenuAction input;
    do
    {
        Console::cls();
        printHeader();

        CMenu menu;
        const auto giftGemAction = menu.createAction({"Gift Gem", 'G'});

        CMenu::ActionList djinnList;

        if (CGameManagement::getInventoryInstance()->hasItem(CGem::gemFilter()))
        {
            djinnList.push_back(giftGemAction);
        }
        menu.addMenuGroup(djinnList);
        input = executeNpcMenu(menu);

        if (input == giftGemAction)
        {
            giftGem();
        }

    } while (input != CMenu::exit());
}

nlohmann::json CBasicDjinn::save() const
{
    return CNpc::save();
}

void CBasicDjinn::load(const nlohmann::json& json)
{
    CNpc::load(json);
}

std::string CBasicDjinn::translatorModuleName() const
{
    return std::string(WonderLamp::moduleName());
}

void CBasicDjinn::printHeader(const bool bFull) const
{
    Console::cls();
    Console::printLn(name(), Console::EAlignment::eCenter);
    if (bFull)
    {
        Console::br();
        Console::printLn(describe(), Console::EAlignment::eCenter);
    }
    Console::br();
}

void CBasicDjinn::giftGem()
{
    auto gem = CGameManagement::getInventoryInstance()->getFirstItemByFilter<CGem>(CGem::gemFilter());
    if (!gem.has_value())
    {
        Console::printLn(tr("Turns out, you dont have a gem."));
        return;
    }

    CGameManagement::getInventoryInstance()->removeItem(gem.value());

    auto sympathy = 10 + Randomizer::getRandom(40);
    if (sympathy > 45)
    {
        Console::printLn(tr("Djinns love gems, more than everything else. {0} eyes are shining, when {1} sees the "
                            "valuable {2}. {1} takes the gem, and puts it into {3} treasury.",
                            name(),
                            heShe(),
                            gem.value()->name(),
                            hisHer()));
    }
    else if (sympathy > 25)
    {
        Console::printLn(
            tr("{0} seems to like your {1}. {2} appreciates your gift.", name(), gem.value()->name(), heShe()));
    }
    else
    {
        Console::printLn(tr("{0} thanks you politely, and puts your {1} into {2} treasury. It is small, and not very "
                            "clear, but it is the gesture that counts, you guess.",
                            name(),
                            gem.value()->name(),
                            hisHer()));
    }

    addSympathy(sympathy);
    Console::br();
}
