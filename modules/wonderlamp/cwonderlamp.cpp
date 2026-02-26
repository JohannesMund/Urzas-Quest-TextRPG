#include "cwonderlamp.h"

#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"
#include "npc/cgenie.h"
#include "npc/cjeannie.h"
#include "npc/djinnfactory.h"
#include "randomizer.h"
#include "wonderlamp/moduleressources.h"

#include <nlohmann/json.hpp>

CWonderLamp::CWonderLamp() : CItem(TagNames::WonderLamp::wonderlamp)
{
    _name = WonderLamp::wonderlamp();
    _description = tr("A beautiful lamp, golden and decorated with gems. Just like in the fairy tales. You should try "
                      "and rub it. Who knows?");
    _isUsableFromInventory = true;
    _isUsableFromBattle = true;
    _isSellable = false;
    _value = 10;

    if (Randomizer::getRandomEntry<Core::EGender>({Core::EGender::eFemale, Core::EGender::eMale}) ==
        Core::EGender::eFemale)
    {
        _djinn = new CJeannie();
    }
    else
    {
        _djinn = new CGenie();
    }
}

CWonderLamp::~CWonderLamp()
{
    if (_djinn == nullptr)
    {
        return;
    }
    if (_djinn->isSignificantOther())
    {
        CGameManagement::getPlayerInstance()->setSignificantOther(nullptr);
    }

    delete _djinn;
}

void CWonderLamp::useFromInventory()
{
    adjustWishes();
    CMenuAction input;
    do
    {
        Console::cls();
        Console::printLn(tr("Your wonderful {}. You want to rub it.", WonderLamp::wonderlamp()));

        CMenu menu(WonderLamp::moduleName());
        const auto rubAction = menu.createAction({"Rub"});
        menu.addMenuGroup({rubAction}, {CMenu::exit()});
        input = menu.execute();

        if (input == rubAction)
        {
            if (_wasted)
            {
                Console::printLn(tr("You rub and rub, but nothing happens. But you can try to rub again."));
            }
            else
            {
                input = CMenu::exit();
                rubTheLamp();
            }
        }
    } while (input != CMenu::exit());
}

void CWonderLamp::useFromBattle(CEnemy*)
{
    useWish();
}

CItem::ItemFilter CWonderLamp::wonderlampFilter()
{
    return [](const CItem* item) { return dynamic_cast<const CWonderLamp*>(item) != nullptr; };
}

nlohmann::json CWonderLamp::save() const
{
    nlohmann::json json = CItem::save();
    json["Wasted"] = _wasted;
    json["wishesLeft"] = _wishesLeft;
    json["Djinn"] = _djinn->save();
    return json;
}

void CWonderLamp::load(const nlohmann::json& json)
{
    CItem::load(json);
    _wasted = json["Wasted"];
    _wishesLeft = json["wishesLeft"];
    _djinn = Djinn::loadFromJson(json["Djinn"]);
}

std::string CWonderLamp::translatorModuleName() const
{
    return std::string(WonderLamp::moduleName());
}

void CWonderLamp::rubTheLamp()
{
    CMenuAction input;
    do
    {
        Console::cls();
        Console::printLn(
            tr("With a lot of smoke, even more sparkling, and a loud \"Wooosh\" noise, {} Appears out of the {}. As "
               "your personal djinn, {} grants you a total of 3 life saving support actions in battle. But also, as "
               "your presonal djinn, rules can be bent when a djinn likes nor dislikes {} master.",
               _djinn->name(),
               WonderLamp::wonderlamp(),
               _djinn->heShe(),
               _djinn->hisHer()));
        Console::br();
        Console::printLn(tr("You have {} wishes left.", _wishesLeft));
        CMenu menu(WonderLamp::moduleName());
        const auto djinnAction = _djinn->npcNav(menu);
        menu.addMenuGroup({djinnAction}, {CMenu::exit()});
        input = menu.execute();
        if (input == djinnAction)
        {
            _djinn->interact();
        }
    } while (input != CMenu::exit());
}

void CWonderLamp::useWish()
{
    adjustWishes();
    _wishesLeft--;
    if (_wishesLeft <= 0)
    {
        destroy();
    }
}

void CWonderLamp::adjustWishes()
{
    if (_djinn->sympathy() > CNpc::ESympathyLevel::eNeutral)
    {
        _wishesLeft = 3;
    }

    if (_djinn->sympathy() == CNpc::ESympathyLevel::eHate)
    {
        _wishesLeft = 1;
    }
}

void CWonderLamp::destroy()
{
    _wasted = true;
    _isUsableFromInventory = false;
    _isUsableFromBattle = false;
    _isSellable = true;
    _description = tr("An old, rusy lamp. This one is junk.");
}
