#include "ckatnottingh.h"
#include "cgamemanagement.h"
#include "cgiftinteraction.h"
#include "ckattalkinteraction.h"
#include "colorize.h"
#include "console.h"
#include "core.h"
#include "rabbitfarm/encounters/cappletree.h"
#include "rabbitfarm/items/capple.h"
#include "rabbitfarm/moduleressources.h"
#include "randomizer.h"

CKatNottingH::CKatNottingH() : CNpc(TagNames::RabbitFarm::kat, Core::EGender::eFemale)
{
    addInteraction(new CGiftInteraction(this, CApple::appleFilter()));
    addInteraction(new CKatTalkInteraction(this));
}

void CKatNottingH::interact()
{
    CNpc::interact();
    CMenuAction input;
    do
    {
        printHeader();
        CMenu menu(RabbitFarm::moduleName());
        input = CNpc::executeNpcMenu(menu);

    } while (input != CMenu::exit());
}

std::string CKatNottingH::name() const
{
    return RabbitFarm::katNottingH();
}

std::string CKatNottingH::describe() const
{
    if (_sympathy > 60)
    {
        return tr("{} is a friendly, really beautiful lady. She is an extraordinaryly {} woman. She has beautiful eyes "
                  "and a breathtaking smile. She is smart and funny. You "
                  "could spend hoours and hours listening to her. Sometimes, you even wish you where a rabbit.",
                  RabbitFarm::katNottingH(),
                  RabbitFarm::coolAndStrong());
    }

    if (_sympathy < 40)
    {
        return tr("{} is a nice woman, she is {}, but her job as Head of the {} also adds some "
                  "eco-hippie flare. You do not like her glasses.",
                  RabbitFarm::katNottingH(),
                  RabbitFarm::coolAndStrong(),
                  RabbitFarm::rabbitHatchName());
    }

    return tr("{} s a friendly, pretty lady. she has a friendly, warm smile and seem to be an extraordinary {} woman. "
              "She is Head of the {} so, obviously, she likes Rabbits. and damn, she is really "
              "pretty! Her {} are uber-cool",
              RabbitFarm::katNottingH(),
              RabbitFarm::coolAndStrong(),
              RabbitFarm::rabbitHatchName(),
              RabbitFarm::katsBoots());
}

nlohmann::json CKatNottingH::save() const
{
    return CNpc::save();
}

void CKatNottingH::load(const nlohmann::json& json)
{
    CNpc::load(json);

    for (const auto& interaction : json[TagNames::Npc::interactions])
    {
        if (CGameStateObject::compareObjectName(TagNames::RabbitFarm::talkInteraction, interaction))
        {
            loadInteraction<CTalkInteraction>(json);
        }
    }
}

std::string CKatNottingH::translatorModuleName() const
{
    return RabbitFarm::moduleName();
}

void CKatNottingH::printHeader(const bool bFull) const
{
    Console::cls();
    Console::printLn(RabbitFarm::katNottingH(), Console::EAlignment::eCenter);
    if (bFull)
    {
        Console::br();
        Console::printLn(describe(), Console::EAlignment::eCenter);
    }
    Console::br();
}
