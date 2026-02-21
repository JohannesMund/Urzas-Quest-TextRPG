#include "ckatnothingh.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "rabbithatch/encounters/crabbithatchappletree.h"
#include "rabbithatch/moduleressources.h"

CKatNothingH::CKatNothingH() : CNpc(TagNames::RabbitHatch::kat, true)
{
}

void CKatNothingH::interact()
{
    CNpc::interact();
    CMenuAction input;
    do
    {
        printHeader();

        CMenu menu(RabbitHatch::moduleName());
        auto appleAction = menu.createAction({"Give her an Apple", 'G'});

        menu.addMenuGroup({appleAction}, {CMenu::exit()});
        input = CNpc::executeNpcMenu(menu);

    } while (input != CMenu::exit());
}

void CKatNothingH::talk()
{
    registerAppleEncounter();
}

void CKatNothingH::thinkAbout()
{
}

std::string CKatNothingH::name() const
{
    return RabbitHatch::katNothingH();
}

std::string CKatNothingH::describe() const
{
    if (_sympathy > 75)
    {
        return tr("{} s a friendly, really beautiful lady. She is an extraordinaryly {}cool{} "
                  "and {}strong{} woman. She has beautiful eyes and a breathtaking smile. She is smart and funny. You "
                  "could spend hoours and hours listening to her. Sometimes, you even wish you where a rabbit.",
                  RabbitHatch::katNothingH(),
                  CC::fgCyan(),
                  CC::ccReset(),
                  CC::fgMagenta(),
                  CC::ccReset());
    }

    if (_sympathy > 75)
    {
        return tr("{} is a nice woman, she is {}cool{} and {}strong{}, but her job as Head of the {} also adds some "
                  "eco-hippie flare. You do not like her glasses.",
                  RabbitHatch::katNothingH(),
                  CC::fgCyan(),
                  CC::ccReset(),
                  CC::fgMagenta(),
                  CC::ccReset(),
                  RabbitHatch::rabbitHatchName());
    }

    return tr("{} s a friendly, pretty lady. she has a friendly, warm smile and seem to be an extraordinary {}cool{} "
              "and {}strong{} woman. She is Head of the {} so, obviously, she likes Rabbits. and damn, she is really "
              "pretty! Her {}B{}oo{}ts{} are uber-cool",
              RabbitHatch::katNothingH(),
              CC::fgCyan(),
              CC::ccReset(),
              CC::fgMagenta(),
              CC::ccReset(),
              RabbitHatch::rabbitHatchName(),
              CC::fgGreen(),
              CC::fgYellow(),
              CC::fgLightYellow(),
              CC::ccReset());
}

nlohmann::json CKatNothingH::save() const
{
    nlohmann::json o;
    o["appleEncounterRegistered"] = _appleEncounterRegistered;
    return o;
}

void CKatNothingH::load(const nlohmann::json& json)
{
    if (json["appleEncounterRegistered"] == true)
    {
        registerAppleEncounter();
    }
}

std::string CKatNothingH::translatorModuleName() const
{
    return RabbitHatch::moduleName();
}

void CKatNothingH::registerAppleEncounter()
{
    if (!_appleEncounterRegistered)
    {
        CGameManagement::getInstance()->registerEncounter(new CRabbitHatchAppleTree(this));
        _appleEncounterRegistered = true;
    }
}

void CKatNothingH::printHeader()
{
    Console::cls();
    Console::printLn(RabbitHatch::katNothingH(), Console::EAlignment::eCenter);
    Console::printLn(describe(), Console::EAlignment::eCenter);
    Console::br();
}
