#include "cmobi.h"

#include "blackivorytower/cdarkmobi.h"
#include "blackivorytower/cpinkfanta.h"
#include "blackivorytower/moduleressources.h"
#include "cbattleinteraction.h"
#include "cdoenerinteraction.h"
#include "cgiftinteraction.h"
#include "colorize.h"
#include "core.h"

#include <format>

CMobi::CMobi() : CNpc(TagNames::BlackIvoryTower::mobi, Core::EGender::eFemale)
{
    addInteraction(new CGiftInteraction(this, CPinkFanta::pinkFantaFilter()));
    addInteraction(new CBattleInteraction(this));
    addInteraction(new CDoenerInteraction(this));
}

void CMobi::interact()
{
    CNpc::interact();
    CMenuAction input;

    do
    {
        CMenu menu(BlackIvoryTower::moduleName());
        input = CNpc::executeNpcMenu(menu);
    } while (input != CMenu::exit());
}

void CMobi::talk()
{
}

std::string CMobi::name() const
{
    return Ressources::Game::mobi();
}

std::string CMobi::describe() const
{
    return std::string();
}

CEnemy* CMobi::enemy() const
{
    return new CDarkMobi(false);
}

std::string CMobi::tatoo() const
{
    return std::format(
        "{0}Döner {1}m{2}acht {1}s{2}chöner{3}", CC::fgYellow(), CC::fgMagenta(), CC::fgWhite(), CC::ccReset());
}

nlohmann::json CMobi::save() const
{

    return CNpc::save();
}

void CMobi::load(const nlohmann::json& json)
{
    for (const auto& interaction : json[TagNames::Npc::interactions])
    {
        if (CGameStateObject::compareObjectName(TagNames::BlackIvoryTower::doener, interaction))
        {
            loadInteraction<CDoenerInteraction>(json);
        }
    }
}

std::string CMobi::translatorModuleName() const
{
    return BlackIvoryTower::moduleName();
}

void CMobi::printHeader(const bool) const
{
}
