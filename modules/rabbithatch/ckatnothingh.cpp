#include "ckatnothingh.h"
#include "colorize.h"
#include "console.h"
#include "rabbithatch/moduleressources.h"
#
CKatNothingH::CKatNothingH() : CNpc(TagNames::RabbitHatch::kat, true)
{
}

void CKatNothingH::interact()
{

    CMenuAction input;
    do
    {
        printHeader();

        CMenu menu(RabbitHatch::moduleName());
        auto appleAction = menu.createAction({"Give her an Apple", 'G'});
        auto foodAction = menu.createAction({"Donate Rabbit food", 'D'});

        menu.addMenuGroup({appleAction, foodAction}, {CMenu::exit()});
        input = CNpc::executeNpcMenu(menu);

    } while (input != CMenu::exit());
}

void CKatNothingH::talk()
{
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
        return tr("{} s a friendly, really beautiful lady. She is an extraordinary {}cool{} "
                  "and {}strong{} woman. She has beautiful brown eyes and a breathtaking. You could spend hoours and "
                  "hours listening to her. Sometimes, you wish you where a rabbit.",
                  RabbitHatch::katNothingH(),
                  CC::fgCyan(),
                  CC::ccReset(),
                  CC::fgMagenta(),
                  CC::ccReset());
    }

    if (_sympathy > 75)
    {
        return tr("{} s a nice woman, she is {}cool{} "
                  "and {}strong{}, but her job as Head of the {} also adds some eco-hippie flare. You do not like her "
                  "glasses.",
                  RabbitHatch::katNothingH(),
                  CC::fgCyan(),
                  CC::ccReset(),
                  CC::fgMagenta(),
                  CC::ccReset(),
                  RabbitHatch::rabbitHatchName());
    }

    return tr(
        "{} s a friendly, pretty lady. she has a friendly, warm smile and seem to be an extraordinary {}cool{} "
        "and {}strong{} woman. She is Head of the {} so, obviously, she likes Rabbits. and damn, she is really pretty!",
        RabbitHatch::katNothingH(),
        CC::fgCyan(),
        CC::ccReset(),
        CC::fgMagenta(),
        CC::ccReset(),
        RabbitHatch::rabbitHatchName());
}

std::string CKatNothingH::translatorModuleName() const
{
    return RabbitHatch::moduleName();
}

void CKatNothingH::printHeader()
{
    Console::cls();
    Console::printLn(RabbitHatch::katNothingH(), Console::EAlignment::eCenter);
    Console::printLn(describe(), Console::EAlignment::eCenter);
    Console::br();
}
