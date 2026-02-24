#include "cnpc.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "jsontagnames.h"

#include <math.h>

CMenuAction CNpc::npcNav(CMenu& menu) const
{
    return menu.createAction({CC::unColorizeString(name())}, false);
}

CNpc::CNpc(const std::string_view& objectName, const bool isFemale) : CGameStateObject(objectName), _female(isFemale)
{
    _favoriteFlower = Ressources::Items::getRandomFlowerType();
    _leastFavoriteFlower = Ressources::Items::getRandomFlowerType();
}

void CNpc::interact()
{
    auto turns = turnsNotSeen();
    setLastSeen();
    if (_sympathy <= 500)
    {
        return;
    }
    if (turns > 50)
    {
        int estrangement =
            CGameManagement::getPlayerInstance()->isSignificantOther(this) ? floor(turns * 0.03) : floor(turns * 0.01);
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
    if (isSignificantOther() && sympathy() < ESympathyLevel::eNeutral)
    {
        Console::printLn(coreTr(
            "It was a wonderful time you had with {} but both of you feel, that it is time to part ways.", name()));
        CGameManagement::getPlayerInstance()->setSignificantOther(nullptr);
    }
}

void CNpc::thinkAbout()
{
    if (isSignificantOther())
    {
        Console::printLn(coreTr("{} is your {}", name(), _female ? coreTr("girlfriend") : coreTr("boyfriend")));
    }
    Console::printLn(coreTr("Your sympathy level is: {}/1000", _sympathy));
    switch (sympathy())
    {
    case ESympathyLevel::eNeutral:
    default:
        Console::printLn(coreTr("You do not care about each other much."));
        break;
    case ESympathyLevel::eLike:
        Console::printLn(coreTr("You like each other."));
        break;
    case ESympathyLevel::eLove:
        Console::printLn(coreTr("This is pure and honest love."));
        break;
    case ESympathyLevel::eDislike:
        Console::printLn(coreTr("You do not like each other too much."));
        break;
    case ESympathyLevel::ehate:
        Console::printLn(coreTr("Its.... complicated."));
        break;
    }
    if (isDatable())
    {
        Console::printLn(coreTr("You really should consider dating."));
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
    o[TagNames::Npc::female] = _female;
    o[TagNames::Npc::lastSeen] = _lastSeen;
    o[TagNames::Npc::isSignificantOther] = isSignificantOther();

    return o;
}

void CNpc::load(const nlohmann::json& json)
{
    _sympathy = json[TagNames::Npc::sympathy];
    _female = json[TagNames::Npc::female];
    _lastSeen = json[TagNames::Npc::lastSeen];

    if (json[TagNames::Npc::isSignificantOther])
    {
        CGameManagement::getPlayerInstance()->setSignificantOther(this);
    }
}

std::string CNpc::heShe() const
{
    return _female ? coreTr("she") : coreTr("he");
}

std::string CNpc::hisHer() const
{
    return _female ? coreTr("her") : coreTr("his");
}

std::string CNpc::himHer() const
{
    return _female ? coreTr("her") : coreTr("him");
}

std::string CNpc::girlfriendBoyfriend() const
{
    return _female ? coreTr("girlfriend") : coreTr("boyfriend");
}

bool CNpc::isSignificantOther() const
{
    return CGameManagement::getPlayerInstance()->isSignificantOther(this);
}

CNpc::ESympathyLevel CNpc::sympathy() const
{
    if (_sympathy > 800)
    {
        return ESympathyLevel::eLove;
    }
    if (_sympathy > 600)
    {
        return ESympathyLevel::eLike;
    }
    if (_sympathy > 400)
    {
        return ESympathyLevel::eNeutral;
    }
    if (_sympathy > 200)
    {
        return ESympathyLevel::eDislike;
    }

    return ESympathyLevel::ehate;
}

bool CNpc::isDatable() const
{
    return _sympathy > 700;
}

void CNpc::setLastSeen(const int i)
{
    _lastSeen = i;
}

void CNpc::setLastSeen()
{
    _lastSeen = CGameManagement::getProgressionInstance()->turns();
}

int CNpc::turnsNotSeen() const
{
    return CGameManagement::getProgressionInstance()->turns() - _lastSeen;
}

std::string CNpc::notSeenString() const
{
    if (turnsNotSeen() > 100)
    {
        return coreTr("a long time");
    }
    if (turnsNotSeen() > 50)
    {
        return coreTr("quite some time");
    }
    return coreTr("a while");
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
    printHeader(false);

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
}

void CNpc::reconcile(const int i)
{
    Console::printLn(coreTr("You feel so much closer to {} now.", name()));
    addSympathy(i * -1);
}
