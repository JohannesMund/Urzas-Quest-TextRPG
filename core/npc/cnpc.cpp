#include "cnpc.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "jsontagnames.h"

#include <math.h>

CMenuAction CNpc::npcNav(CMenu& menu)
{
    return menu.createAction({CC::unColorizeString(name())}, false);
}

CNpc::CNpc(const std::string_view& objectName, const bool isFemale) : CGameStateObject(objectName), _female(isFemale)
{
}

void CNpc::interact()
{
    int turnsNotSeen = CGameManagement::getProgressionInstance()->turns() - _lastSeen;
    _lastSeen = CGameManagement::getProgressionInstance()->turns();
    if (_sympathy <= 500)
    {
        return;
    }
    if (turnsNotSeen > 50)
    {
        int estrangement = CGameManagement::getPlayerInstance()->isSignificantOther(this) ? floor(turnsNotSeen * -0.03)
                                                                                          : floor(turnsNotSeen * -0.01);
        estrange(estrangement);
    }
    breakUp();
    Console::confirmToContinue();
}

void CNpc::askOut()
{
    if (!isSignificantOther())
    {
        CGameManagement::getPlayerInstance()->setSignificantOther(this);
    }
}

void CNpc::breakUp()
{
    if (isSignificantOther() && _sympathy < 500)
    {
        Console::printLn(coreTr(
            "It was a wonderful time you had with {} but both of you feel, that it is time to part ways.", name()));
        CGameManagement::getPlayerInstance()->setSignificantOther(nullptr);
    }
}

bool CNpc::addSympathy(const int i)
{
    int originalSympathy = _sympathy;

    _sympathy += i;
    if (_sympathy < 0)
    {
        _sympathy = 0;
    }

    if (_sympathy > 1000)
    {
        _sympathy = 1000;
    }

    int diff = _sympathy - originalSympathy;

    if (diff > 0)
    {
        Console::printLn(coreTr("{} now likes you {} better", name(), diff > 100 ? "much" : ""));
    }

    if (diff < 0)
    {
        Console::printLn(coreTr("{} now likes you {} less", name(), diff < -100 ? "much" : ""));
    }

    return false;
}

nlohmann::json CNpc::save() const
{
    nlohmann::json o;
    o[TagNames::Npc::sympathy] = _sympathy;
    return o;
}

void CNpc::load(const nlohmann::json& json)
{
    _sympathy = json[TagNames::Npc::sympathy];
}

std::string CNpc::heShe() const
{
    return _female ? coreTr("she") : coreTr("he");
}

std::string CNpc::hisHer() const
{
    return _female ? coreTr("her") : coreTr("his");
}

bool CNpc::isSignificantOther() const
{
    return CGameManagement::getPlayerInstance()->isSignificantOther(this);
}

CMenuAction CNpc::executeNpcMenu(CMenu& menu)
{
    auto talkActionString = coreTr("Talk to {}", CC::unColorizeString(name()));
    auto thinkAboutActionString = coreTr("Think about {}", CC::unColorizeString(name()));
    auto askOutActionString = coreTr("Ask {} for a date", CC::unColorizeString(name()));

    auto talkAction = menu.createAction({talkActionString, 'T'});
    auto thinkAboutAction = menu.createAction({thinkAboutActionString, 'i'});
    auto askOutAction = menu.createAction({askOutActionString, 'A'});

    CMenu::ActionList actions;
    actions.push_back(talkAction);
    actions.push_back(thinkAboutAction);

    if (_sympathy > 750)
    {
        actions.push_back(askOutAction);
    }

    menu.addMenuGroup(actions);

    auto input = menu.execute();

    if (input == talkAction)
    {
        talk();
    }

    if (input == thinkAboutAction)
    {
        thinkAbout();
    }

    return input;
}

std::string CNpc::translatorObjectName() const
{
    return std::string(TagNames::Translator::npc);
}

void CNpc::estrange(const int i)
{
    Console::printLn(
        coreTr("{} and you have not seen for each other for quite a while. You feel a little estranged", name()));
    addSympathy(i);
    if (_sympathy < 500)
    {
        _sympathy = 500;
    }
}
