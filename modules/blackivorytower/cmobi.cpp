#include "cmobi.h"

#include "blackivorytower/moduleressources.h"
#include "colorize.h"
#include "core.h"

CMobi::CMobi() : CNpc(TagNames::BlackIvoryTower::mobi, Core::EGender::eFemale)
{
}

void CMobi::interact()
{
    CNpc::interact();
    CMenuAction input;
}

void CMobi::talk()
{
}

std::string CMobi::name() const
{
    return std::string();
}

std::string CMobi::describe() const
{
    return std::string();
}

CMenuAction CMobi::npcNav(CMenu& menu) const
{
    return menu.createAction({CC::unColorizeString(Ressources::Game::mobi())});
}

std::string CMobi::translatorModuleName() const
{
    return BlackIvoryTower::moduleName();
}

void CMobi::printHeader(const bool) const
{
}
