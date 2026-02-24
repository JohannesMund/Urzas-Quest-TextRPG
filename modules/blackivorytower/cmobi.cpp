#include "cmobi.h"

#include "blackivorytower/moduleressources.h"
#include "colorize.h"

CMobi::CMobi() : CNpc(TagNames::BlackIvoryTower::mobi, true)
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
