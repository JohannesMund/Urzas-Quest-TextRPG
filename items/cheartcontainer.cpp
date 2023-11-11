#include "cheartcontainer.h"
#include "cgamemanagement.h"
#include "console.h"

CHeartContainer::CHeartContainer() : CItem()
{
    _name = "Heart Container";
    _description = "A strange looking thing. A heart-shaped glass flask, filled with a deep red liquid.";

    _value = 6000;
    _isConsumable = true;
    _isUsableFromInventory = true;
    _isUsableFromBattle = true;
    _isSellable = true;
}

void CHeartContainer::useFromInventory()
{
    Console::printLn("Let's do it. You drink the content from the flask, and the flask disappears as soon as it is "
                     "empty. You feel a lot fitter.");
    CGameManagement::getPlayerInstance()->addMaxHp(1);
}
