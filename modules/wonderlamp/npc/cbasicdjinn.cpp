#include "cbasicdjinn.h"

#include "cgamemanagement.h"
#include "cgiftinteraction.h"
#include "cmenu.h"
#include "console.h"
#include "core.h"
#include "randomizer.h"
#include "wonderlamp/items/cgem.h"
#include "wonderlamp/moduleressources.h"

CBasicDjinn::CBasicDjinn(const Core::EGender gender) : CNpc(TagNames::WonderLamp::djinn, gender)
{
    addInteraction(new CGiftInteraction(this, CGem::gemFilter()));
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
        input = executeNpcMenu(menu);

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
