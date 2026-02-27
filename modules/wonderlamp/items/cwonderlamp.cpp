#include "cwonderlamp.h"

#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"
#include "randomizer.h"
#include "wonderlamp/items/cgem.h"
#include "wonderlamp/moduleressources.h"
#include "wonderlamp/npc/cgenie.h"
#include "wonderlamp/npc/djinnfactory.h"

#include <math.h>
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
    _lastCaredFor = std::max(1U, CGameManagement::now() - Randomizer::getRandom(50));

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
        Console::printLn(
            tr("Your wonderful {}. You want to rub it. You always want to rub ist, but you also want to care about "
               "this precious artifact. It probably needs some cleaning, and a little repair now and then.",
               WonderLamp::wonderlamp()));

        CMenu menu(WonderLamp::moduleName());
        const auto rubAction = menu.createAction({"Rub", 'R'});
        const auto examineAction = menu.createAction({"Examine", 'E'});
        menu.addMenuGroup({rubAction, examineAction}, {CMenu::exit()});
        input = menu.execute();

        if (input == examineAction)
        {
            examine();
        }

        if (input == rubAction)
        {
            rubTheLamp();
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
    json["WishesLeft"] = _wishesLeft;
    json["MissingGem"] = _missingGem;
    json["LastCaredFor"] = _lastCaredFor;

    json["Djinn"] = _djinn->save();

    return json;
}

void CWonderLamp::load(const nlohmann::json& json)
{
    CItem::load(json);

    _wasted = json["Wasted"];
    _wishesLeft = json["WishesLeft"];
    _missingGem = json["MissingGem"];
    _lastCaredFor = json["LastCaredFor"];

    _djinn = Djinn::loadFromJson(json["Djinn"]);
}

std::string CWonderLamp::translatorModuleName() const
{
    return std::string(WonderLamp::moduleName());
}

void CWonderLamp::rubTheLamp()
{
    if (_wasted)
    {
        Console::printLn(tr("You rub and rub, but nothing happens. But you can try to rub again."));
        Console::br();
        Console::confirmToContinue();
        return;
    }

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

void CWonderLamp::examine()
{
    if (_wasted)
    {
        Console::printLn(tr("You take a close look at your {}. It is dirty, it is broken and most important: "
                            "it is empty. it is a worthless piece of trash. You do not bother to clean it.",
                            WonderLamp::wonderlamp()));
        Console::br();
        Console::confirmToContinue();
        return;
    }

    CMenuAction input;

    do
    {
        CMenu menu(WonderLamp::moduleName());

        auto cleanAction = menu.createAction({"Clean", 'C'});
        auto replaceAction = menu.createAction({"Replace missing gem", 'R'});

        CMenu::ActionList careList;

        if (needsCleaning())
        {
            Console::printLn(tr("You can see, that your {} is loved and used often. The polish is getting dull and "
                                "some scratches appear"));
            const auto decay = CGameManagement::now() - _lastCaredFor;
            _missingGem = _missingGem || Randomizer::getRandom(decay) > 50;
            careList.push_back(cleanAction);
        }

        if (_missingGem)
        {
            Console::printLn(
                tr("Turns out, there is a gem missing on your {}. You should replace it.", WonderLamp::wonderlamp()));
            if (CGameManagement::getInventoryInstance()->hasItem(CGem::CGem::gemFilter()))
            {
                careList.push_back(replaceAction);
            }
            else
            {
                tr("Unfortunately, you do not have gems, so you should keep your eyes open.");
            }
        }

        menu.addMenuGroup(careList, {CMenu::exit()});
        input = menu.execute();

        if (input == cleanAction)
        {
            clean();
        }
        if (input == replaceAction)
        {
            replaceGem();
        }

    } while (input == CMenu::exit());
}

void CWonderLamp::replaceGem()
{
    if (!CGameManagement::getInventoryInstance()->hasItem(CGem::gemFilter()))
    {
        Console::printLn(tr("You dont have a gem. maybe later."));
        return;
    }

    auto items = CGameManagement::getInventoryInstance()->getItemsByFilter(CGem::gemFilter());
    if (items.size() == 0)
    {
        Console::printLn(tr("You dont have a gem. maybe later."));
        return;
    }

    auto gem = items[0];
    Console::printLn(tr("There is a gap on your {} where the gem fell of. You decide to replace it with a beautiful "
                        "{}. Looks like new.",
                        WonderLamp::wonderlamp(),
                        gem->name()));
    Console::printLn(tr("{} seems to like the new gem.", _djinn->name()));
    _djinn->addSympathy(25 + Randomizer::getRandom(25));
    if (needsCleaning())
    {
        Console::br();
        Console::printLn(
            tr("The {} might be new, and it sparkles beautifully. But your {} should use another cleaning.",
               gem->name(),
               WonderLamp::wonderlamp()));
    }
    CGameManagement::getInventoryInstance()->removeItem(gem);

    Console::br();
    Console::confirmToContinue();
}

void CWonderLamp::clean()
{
    Console::printLn(tr("You take some time, and clean your {}. Carefully you remove dirt, polish out the scratches "
                        "and let the gems shine again.",
                        WonderLamp::wonderlamp()));
    if (_missingGem)
    {
        Console::printLn(tr("Speaking of shiny gems, one is missing, you should replace it soon."));
    }

    Console::br();
    Console::printLn(tr("Finally, the home of {} is nice and clean again", _djinn->name()));
    _djinn->addSympathy(5 + Randomizer::getRandom(20));

    _lastCaredFor = CGameManagement::now();
    Console::br();
    Console::confirmToContinue();
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

bool CWonderLamp::needsCleaning()
{
    const auto decay = CGameManagement::now() - _lastCaredFor;
    return decay > 25;
}
