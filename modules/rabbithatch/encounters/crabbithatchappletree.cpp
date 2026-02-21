#include "crabbithatchappletree.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "console.h"
#include "rabbithatch/ckatnothingh.h"
#include "rabbithatch/items/crabbithatchapple.h"
#include "rabbithatch/moduleressources.h"

CRabbitHatchAppleTree::CRabbitHatchAppleTree(CKatNothingH* kat) : _kat(kat)
{
    _isSingleExecution = false;
    _type = CEncounter::eField;
}

void CRabbitHatchAppleTree::execute(const std::string_view&)
{
    CRabbithatchApple* apple = new CRabbithatchApple;
    Console::printLn(tr("This is one huge {0} tree. It is huge, majestic and full of beautiful {0}s. The {0}s look "
                        "ripe, fresh and juicy.",
                        apple->name()));
    if (_kat->isSignificantOther())
    {
        Console::printLn(tr("You cannot help to think about your girlfried {}. She loves {}s. You should get her one.",
                            _kat->name(),
                            apple->name()));
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
                   apple->name()));
        }
        else
        {
            Console::printLn(tr("You start thinking, wasn't there this rabbit lady? {} or whatever was their name? "
                                "Didn't she tell you about {}s?",
                                _kat->name(),
                                apple->name()));
        }
    }

    CMenu menu(RabbitHatch::moduleName());
    CMenuAction pickAction = menu.createAction({"Pick an Apple", 'P'});

    menu.addMenuGroup({pickAction}, {CMenu::exit()});

    if (menu.execute() == pickAction)
    {
        if (_kat->isSignificantOther())
        {
            Console::printLn(tr("You pick an {} for {}. She will love it.", apple->name(), _kat->name()));
        }
        else
        {
            if (_kat->sympathy() >= CKatNothingH::ESympathyLevel::eLove)
            {
                Console::printLn(tr("You select an extra beautiful, extra juicy {} for {}. You hope she will like it. "
                                    "You imagine her smile and her beautiful eyes, when you give it to her.",
                                    apple->name(),
                                    _kat->name()));
            }
            else
            {
                Console::printLn(tr("An {} for the rabbit lady. She will like it", apple->name()));
            }
        }
        CGameManagement::getInventoryInstance()->addItem(apple);
    }
    else
    {
        Console::printLn(
            tr("{0}s are over estimated. And your pockets are full enough even without a rotting {0}", apple->name()));
        delete apple;
    }
}

unsigned int CRabbitHatchAppleTree::encounterChance(const EEncounterType&, const std::string_view&) const
{
    return 5;
}

std::string CRabbitHatchAppleTree::name() const
{
    return tr("Apple tree");
}

std::string CRabbitHatchAppleTree::moduleName() const
{
    return RabbitHatch::moduleName();
}

std::string CRabbitHatchAppleTree::translatorModuleName() const
{
    return RabbitHatch::moduleName();
}
