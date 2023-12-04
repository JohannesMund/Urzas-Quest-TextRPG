#include "clayla2encounter.h"
#include "cbattle.h"
#include "cgamemanagement.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "layla2/encounters/clayla2goblinencounter.h"
#include "layla2/enemies/claylabossguards.h"
#include "layla2/moduleressources.h"

#include <format>

CLayla2Encounter::CLayla2Encounter()
{
    _isSingleExecution = true;
    _type = CEncounter::eField;
}

void CLayla2Encounter::execute(const std::string_view&)
{
    Console::printLn(
        std::format("While walking through the land and doing adventurers things, you hear a well-known {}s{}cream{}. "
                    "You follow the noise, and sure see your favourite damsel in distress, {} tied up on the back of a "
                    "cart, guarded by two of the {}g{}uards{} you remember very well from last time.",
                    CC::fgMagenta(),
                    CC::fgLightMagenta(),
                    CC::ccReset(),
                    Ressources::Game::princessLayla(),
                    CC::fgBlue(),
                    CC::fgYellow(),
                    CC::ccReset()));
    Console::printLn("She sees you, and even though she is gagged, her eyes are screaming for help. And man, sh is "
                     "hot! So, a man's gotta do, what a man's gotta do.");
    Console::br();
    Console::printLn("Do you want to help?");

    CMenu menu;
    menu.addMenuGroup({menu.createAction("Help"), menu.createAction("Ignore")});
    if (menu.execute().key == 'i')
    {
        Console::printLn("This event is story-relevat, thats clear, so you can just ignore it for now, and wait until "
                         "it happens again.");
        return;
    }

    CLaylaBossGuards boss;
    boss.printBossBattleHeader();
    Console::printLn(std::format(
        "Hoping, that it does work better than last time, you make the most heroic pose, you can think of, scream \"I "
        "am coming for your rescue, princess\" in the direction of {}, and attack the two guards.",
        Ressources::Game::princessLayla()));
    Console::br();
    Console::confirmToContinue();

    CBattle battle(&boss);
    battle.fight();

    if (CGameManagement::getPlayerInstance()->isDead())
    {
        return;
    }
    Console::confirmToContinue();
    Console::printLn(std::format("While untying {}, you ask how she got abducted again, and she tells you, that the "
                                 "royal guards just failed to bring her home. the journey took days, and eventually, "
                                 "the trek was ambushed and she found herself tied up on the back of this cart.",
                                 Ressources::Game::layla()));
    Console::printLn(
        "You promise her, that this will not happen again, because this time, you will be the one escorting her to the "
        "capital. You feel brave and heroic and she does not seem to be very impressed.");
    Console::br();
    Console::printLn(std::format(
        "Eventually, she sees your tatoo. {}\"What does that mean?\"{}, she asks. \"Probably, that it is a bad idea to "
        "get black-out drunk in the darkes and shadiest area of the city\", is your bitter reply.",
        CC::fgLightMagenta(),
        CC::ccReset()));
    Console::printLn(std::format("During the kidnapping, she lost her {0}, the {0} gifted to her by her grandmother. "
                                 "Sha cannot return home without this {0}.",
                                 Ressources::Game::laylasRibbon()));
    Console::printLn(std::format("You start to understand, that the royal guards probably are not totally incompetent, "
                                 "but what man could refuse the wich of beautiful woman like {}.",
                                 Ressources::Game::princessLayla()));
    Console::br();
    CGameManagement::getInstance()->registerEncounter(new CLayla2GoblinEncounter());

    _hasBeenExecuted = true;
}

unsigned int CLayla2Encounter::encounterChance(const EEncounterType&, const std::string_view&) const
{
    return 5;
}

std::string CLayla2Encounter::name() const
{
    return Layla2Ressources::encounterNameGuards();
}

std::string CLayla2Encounter::moduleName() const
{

    return std::format(
        "{1}Kidnapped {0}P{1}rincess{2}... Again!", CC::fgLightMagenta(), CC::fgLightBlue(), CC::ccReset());
}
