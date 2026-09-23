#include "cnpc.h"
#include "cbattleinteraction.h"
#include "cdateinteraction.h"
#include "cflowerinteraction.h"
#include "cgamemanagement.h"
#include "cgiftinteraction.h"
#include "cnpcenemy.h"
#include "colorize.h"
#include "console.h"
#include "jsontagnames.h"
#include "randomizer.h"

#include <math.h>

std::string CNpc::tattoo() const
{
    return std::format("{0}<3{1} {2} {0}<3{1}", CC::fgLightRed(), CC::ccReset(), name());
}

const CMenuAction CNpc::npcNav(CMenu& menu) const
{
    return menu.createAction({CC::unColorizeString(name())}, false);
}

CNpc::CNpc(const std::string_view& objectName, const Core::EGender gender) :
    CGameStateObject(objectName),
    _gender(gender)
{
    addInteraction(new CFlowerInteraction(this));
    addInteraction(new CDateInteraction(this));
}

CNpc::~CNpc()
{
    clearInteractions();
}

void CNpc::interact()
{
    auto turns = turnsNotSeen();
    setLastSeen();

    if (turns > 50)
    {
        int estrangement =
            CGameManagement::getPlayerInstance()->isSignificantOther(this) ? floor(turns * 0.03) : floor(turns * 0.01);
        estrange(estrangement);
    }
    breakUp();
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
        Console::printLn(coreTr("{} is your {}", name(), girlfriendBoyfriend()));
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
    case ESympathyLevel::eHate:
        Console::printLn(coreTr("Its.... complicated."));
        break;
    }
    if (isDatable())
    {
        Console::br();
        Console::printLn(coreTr("You really should consider dating."));
    }
    Console::br();
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
    o[TagNames::Npc::gender] = _gender;
    o[TagNames::Npc::lastSeen] = _lastSeen;
    o[TagNames::Npc::isSignificantOther] = isSignificantOther();

    for (const auto& interaction : _interactions)
    {
        auto i = interaction->save();
        i[TagNames::Common::objectName] = interaction->getObjectName();
        o[TagNames::Npc::interactions].push_back(i);
    }

    return o;
}

void CNpc::load(const nlohmann::json& json)
{
    _sympathy = json[TagNames::Npc::sympathy];
    _gender = json[TagNames::Npc::gender];
    _lastSeen = json[TagNames::Npc::lastSeen];

    if (json[TagNames::Npc::isSignificantOther])
    {
        CGameManagement::getPlayerInstance()->setSignificantOther(this);
    }

    for (const auto& interaction : json[TagNames::Npc::interactions])
    {
        if (CGameStateObject::compareObjectName(TagNames::NpcInteractions::flower, interaction))
        {
            loadInteraction<CFlowerInteraction>(interaction);
        }

        if (CGameStateObject::compareObjectName(TagNames::NpcInteractions::date, interaction))
        {
            loadInteraction<CDateInteraction>(interaction);
        }

        if (CGameStateObject::compareObjectName(TagNames::NpcInteractions::battle, interaction))
        {
            loadInteraction<CBattleInteraction>(interaction);
        }
        if (CGameStateObject::compareObjectName(TagNames::NpcInteractions::gift, interaction))
        {
            loadInteraction<CGiftInteraction>(interaction);
        }
    }
}

std::string CNpc::heShe() const
{
    return _gender == Core::EGender::eFemale ? coreTr("she") : coreTr("he");
}

std::string CNpc::hisHer() const
{
    return _gender == Core::EGender::eFemale ? coreTr("her") : coreTr("his");
}

std::string CNpc::himHer() const
{
    return _gender == Core::EGender::eFemale ? coreTr("her") : coreTr("him");
}

std::string CNpc::girlfriendBoyfriend() const
{
    return _gender == Core::EGender::eFemale ? coreTr("girlfriend") : coreTr("boyfriend");
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

    return ESympathyLevel::eHate;
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
    _lastSeen = CGameManagement::now();
}

int CNpc::turnsNotSeen() const
{
    return CGameManagement::now() - _lastSeen;
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

CEnemy* CNpc::enemy() const
{
    return new CNpcEnemy(this);
}

CMenuAction CNpc::executeNpcMenu(CMenu& menu)
{
    auto thinkAboutActionString = coreTr("Think about {}", CC::unColorizeString(name()));
    auto thinkAboutAction = menu.createAction({thinkAboutActionString, 'i'});
    menu.addMenuGroup({thinkAboutAction}, {CMenu::exit()});

    CMenu::ActionList actions;

    for (const auto interaction : _interactions)
    {
        if (interaction->interactionAvailable())
        {
            auto nav = interaction->nav(menu);
            actions.push_back(nav);
        }
    }

    menu.addMenuGroup({actions});

    auto input = menu.execute();
    printHeader(false);

    auto it =
        std::find_if(_interactions.begin(), _interactions.end(), [&input](const auto i) { return i->checkNav(input); });

    if (it != _interactions.end())
    {
        (*it)->executeInteraction();
        Console::confirmToContinue();
        return input;
    }

    if (input == thinkAboutAction)
    {
        thinkAbout();
        Console::confirmToContinue();
        return input;
    }

    return input;
}

std::string CNpc::translatorObjectName() const
{
    return std::string(TagNames::Translator::npc);
}

void CNpc::addInteraction(CNpcInteraction* interaction)
{
    _interactions.push_back(interaction);
}

void CNpc::clearInteractions()
{
    for (auto interaction : _interactions)
    {
        delete interaction;
    }
}

void CNpc::estrange(const int i)
{
    if (_sympathy > 500)
    {
        Console::printLn(
            coreTr("{} and you have not seen for each other for quite a while. You feel a little estranged", name()));
        addSympathy(i * -1);
        _sympathy = std::max(500, _sympathy);
    }
    if (_sympathy < 500)
    {
        Console::printLn(coreTr("{} and you have not seen for each other for quite a while. Old grudges fade", name()));
        addSympathy(i);
        _sympathy = std::min(500, _sympathy);
    }
}

void CNpc::reconcile(const int i)
{
    Console::printLn(coreTr("You feel so much closer to {} now.", name()));
    addSympathy(i * -1);
}
