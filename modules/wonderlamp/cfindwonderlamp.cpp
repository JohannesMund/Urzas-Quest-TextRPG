#include "cfindwonderlamp.h"

#include "cgamemanagement.h"
#include "console.h"
#include "ctown.h"
#include "items/cgem.h"
#include "items/cwonderlamp.h"
#include "wonderlamp/moduleressources.h"

CFindWonderLamp::CFindWonderLamp()
{
    _isSingleExecution = true;
    _type = CEncounter::eTown;
}

void CFindWonderLamp::execute(const std::string_view& moduleName)
{
    std::string townName;
    auto town = dynamic_cast<CTown*>(CGameManagement::getInstance()->currentRoom());
    if (town != nullptr)
    {
        townName = town->name();
    }

    Console::printLn(tr("Wandering through the darker corners of {} you see a pile of junk in the corner of a dark "
                        "alley. On top of the pile is a strange old lamp, which looks intriguing",
                        town->name()));
    Console::printLn(tr("Take a closer look?"));
    if (CMenu::executeYesNoMenu() == CMenu::no())
    {
        Console::printLn(tr("Other people trash is not your treasure. You ignore the lamp, and continue your way."));
        Console::br();
        Console::confirmToContinue();
        return;
    }
    Console::printLn(tr("Other peoples trash is not your treasure. You ignore the lamp, and continue your way."));
    Console::printLn(tr("Other peoples trash could be your treasure. You pick up the lamp and examine it closely. It "
                        "is an old lamp a little dirty but covered in gems."));
    Console::printLn(tr("This looks precious. Take it?"));
    if (CMenu::executeYesNoMenu() == CMenu::no())
    {
        Console::printLn(tr("Other peoples trash is not your treasure. You ignore the lamp, and "
                            "continue your way."));
        Console::br();
        Console::confirmToContinue();
        return;
    }
    auto wonderlamp = new CWonderLamp();
    Console::printLn(
        tr("This looks really precious. It is a little dirty, but you are pretty sure, that you found a {}. "
           "But before you can take a closer look, you have to leave. this alley is really dark, and really "
           "creepy. You put the lamp into your bag and continue your way.",
           wonderlamp->name()));

    CGameManagement::getInventoryInstance()->addItem(wonderlamp);
    CGameManagement::getItemFactoryInstance()->registerLootItemGenerator(moduleName, []() { return new CGem(); }, 1);
}

unsigned int CFindWonderLamp::encounterChance(const EEncounterType&, const std::string_view&) const
{
    if (CGameManagement::getProgressionInstance()->currentGameStage() >= Module::EGameStage::eProvenAsHero)
    {
        return 1;
    }
    return 0;
}

std::string CFindWonderLamp::name() const
{
    return WonderLamp::wonderLampEncounter();
}

std::string CFindWonderLamp::moduleName() const
{
    return WonderLamp::moduleName();
}

std::string CFindWonderLamp::translatorObjectName() const
{
    return std::string(TagNames::WonderLamp::findWonderlamp);
}
