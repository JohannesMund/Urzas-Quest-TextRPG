#include "cappletree.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"
#include "rabbitfarm/ckatnothingh.h"
#include "rabbitfarm/items/capple.h"
#include "rabbitfarm/moduleressources.h"

CAppleTree::CAppleTree(CKatNothingH* kat) : _kat(kat)
{
    _isSingleExecution = false;
    _type = CEncounter::eField;
}

void CAppleTree::execute(const std::string_view&)
{
    CEncounter::execute();
    Console::br();
    Console::printLn(tr("This is one huge {0} tree. It is huge, majestic and full of beautiful {0}s. The {0}s look "
                        "ripe, fresh and juicy.",
                        RabbitFarm::apple()));
    if (_kat->isSignificantOther())
    {
        Console::printLn(tr("You cannot help to think about your girlfried {}. She loves {}s. You should get her one.",
                            _kat->name(),
                            RabbitFarm::apple()));
    }
    else
    {
        if (_kat->sympathy() >= CKatNothingH::ESympathyLevel::eLove)
        {
            Console::printLn(tr("You cannot stop thinkung about {} her smile, her beautiful eyes, her bell-like "
                                "laughter. You feel obligated to get something nice for her.",
                                _kat->name()));
        }
        else if (_kat->sympathy() >= CKatNothingH::ESympathyLevel::eLike)
        {
            Console::printLn(
                tr("You remember {}. she is a relly nice lady, and she likes {}s. Maybe you can get one for her?",
                   _kat->name(),
                   RabbitFarm::apple()));
        }
        else
        {
            Console::printLn(tr("You start thinking, wasn't there this rabbit lady? {} or whatever was their name? "
                                "Didn't she tell you about {}s?",
                                _kat->name(),
                                RabbitFarm::apple()));
        }
    }
    Console::br();
    CMenu menu(RabbitFarm::moduleName());
    CMenuAction pickAction = menu.createAction({"Pick an Apple", 'P'});

    menu.addMenuGroup({pickAction}, {CMenu::exit()});

    if (menu.execute() == pickAction)
    {
        if (_kat->isSignificantOther())
        {
            Console::printLn(tr("You pick an {} for {}. She will love it.", RabbitFarm::apple(), _kat->name()));
        }
        else
        {
            if (_kat->sympathy() >= CKatNothingH::ESympathyLevel::eLove)
            {
                Console::printLn(tr("You select an extra beautiful, extra juicy {} for {}. You hope she will like it. "
                                    "You imagine her smile and her beautiful eyes, when you give it to her.",
                                    RabbitFarm::apple(),
                                    _kat->name()));
            }
            else
            {
                Console::printLn(tr("An {} for the rabbit lady. She will like it", RabbitFarm::apple()));
            }
        }
        CGameManagement::getInventoryInstance()->addItem(new CApple);
    }
    else
    {
        Console::printLn(tr("{0}s are over estimated. And your pockets are full enough even without a rotting {0}",
                            RabbitFarm::apple()));
    }
}

unsigned int CAppleTree::encounterChance(const EEncounterType& tp, const std::string_view&) const
{
    if (tp == EEncounterType::eField)
    {
        return 5;
    }
    return 0;
}

std::string CAppleTree::name() const
{
    return tr("Apple tree");
}

std::string CAppleTree::moduleName() const
{
    return RabbitFarm::moduleName();
}

std::string CAppleTree::translatorObjectName() const
{
    return std::string(TagNames::RabbitFarm::appleEncounter);
}
