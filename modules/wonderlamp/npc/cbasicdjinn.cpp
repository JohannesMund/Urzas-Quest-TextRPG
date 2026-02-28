#include "cbasicdjinn.h"

#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"
#include "core.h"
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
    return nlohmann::json();
}

void CBasicDjinn::load(const nlohmann::json&)
{
}

std::string CBasicDjinn::translatorModuleName() const
{
    return std::string(WonderLamp::moduleName());
}

void CBasicDjinn::giftGem()
{
}
