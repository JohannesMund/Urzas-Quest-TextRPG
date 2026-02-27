#include "cnpc.h"
#include "cflower.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "jsontagnames.h"
#include "randomizer.h"

#include <math.h>

CMenuAction CNpc::npcNav(CMenu& menu) const
{
    return menu.createAction({CC::unColorizeString(name())}, false);
}

CNpc::CNpc(const std::string_view& objectName, const Core::EGender gender) :
    CGameStateObject(objectName),
    _gender(gender)
{
    _favoriteFlower = Ressources::Items::getRandomFlowerType();
    _leastFavoriteFlower = Ressources::Items::getRandomFlowerType();
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

void CNpc::giftFlower()
{
    auto flowers = CGameManagement::getInventoryInstance()->getItemsByFilter(CFlower::flowerFilter());
    if (!flowers.size())
    {
        Console::printLn(
            coreTr("Well, this is emberrassing. You search your bag for flowers, but apperently you have none."));
        Console::printLn(coreTr("{} looks dissapointed.", name()));
        return;
    }
    auto oneFlower = dynamic_cast<CFlower*>(flowers.at(0));
    if (oneFlower == nullptr)
    {
        Console::printLn(coreTr("Your flower crumbles to dust in your hand."));
        Console::printLn(coreTr("{} looks dissapointed.", name()));
        return;
    }
    Console::printLn(coreTr("You draw a {} out of your bag and hand it over to {}", oneFlower->name(), name()));
    switch (sympathy())
    {
    case ESympathyLevel::eHate:
        Console::printLn(coreTr(
            "You and {}, this did not go together well up to now. {} accepts the flower anyway.", name(), heShe()));
        break;
    case ESympathyLevel::eDislike:
        Console::printLn(coreTr(
            "You and {}, are not frieds at all. {} accepts the flower anyway as a peace offer.", name(), heShe()));
        break;
    case ESympathyLevel::eNeutral:
    default:
        Console::printLn(coreTr("{} is surprised about your gift and {} takes it with a smile.", name(), heShe()));
        break;
    case ESympathyLevel::eLike:
        Console::printLn(
            coreTr("Your geasture hit the spot for {}. With a smile, {} accepts your gift.", name(), heShe()));
        break;
    case ESympathyLevel::eLove:
        Console::printLn(
            coreTr("A gift of love for {0}, {1} smiles as {1} taks your precious flower.", name(), heShe()));
        break;
    }

    if (oneFlower->flowerType() == _favoriteFlower && oneFlower->flowerType() != _leastFavoriteFlower)
    {
        Console::printLn(coreTr("{}s are {}s favourite flowers. {} loves your gift.",
                                Ressources::Items::flower2String(oneFlower->flowerType()),
                                name(),
                                heShe()));
        addSympathy(20 + Randomizer::getRandom(30));
    }
    else if (oneFlower->flowerType() == _leastFavoriteFlower && oneFlower->flowerType() != _favoriteFlower)
    {
        Console::printLn(coreTr("{} hates {}s. {} accepts your gesture.",
                                name(),
                                Ressources::Items::flower2String(oneFlower->flowerType()),
                                heShe()));
        addSympathy(5 + Randomizer::getRandom(10));
    }
    else
    {
        Console::printLn(coreTr("{} like {}s. {} takes the flowers with a smile.",
                                Ressources::Items::flower2String(oneFlower->flowerType()),
                                name(),
                                heShe()));
        addSympathy(5 + Randomizer::getRandom(10));
    }

    CGameManagement::getInventoryInstance()->removeItem(oneFlower);
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
    o[TagNames::Npc::favouriteFlower] = _favoriteFlower;
    o[TagNames::Npc::leastFavouriteFlower] = _leastFavoriteFlower;
    return o;
}

void CNpc::load(const nlohmann::json& json)
{
    _sympathy = json[TagNames::Npc::sympathy];
    _gender = json[TagNames::Npc::gender];
    _lastSeen = json[TagNames::Npc::lastSeen];
    _favoriteFlower = json[TagNames::Npc::favouriteFlower];
    _leastFavoriteFlower = json[TagNames::Npc::leastFavouriteFlower];

    if (json[TagNames::Npc::isSignificantOther])
    {
        CGameManagement::getPlayerInstance()->setSignificantOther(this);
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

CMenuAction CNpc::executeNpcMenu(CMenu& menu)
{
    const auto thinkAboutActionString = coreTr("Think about {}", CC::unColorizeString(name()));
    const auto thinkAboutAction = menu.createAction({thinkAboutActionString, 'i'});
    menu.addMenuGroup({thinkAboutAction}, {CMenu::exit()});

    const auto talkAction = menu.createAction({"Talk", 'T'});
    const auto askOutAction = menu.createAction({"Ask out", 'A'});
    const auto giftFlowerAction = menu.createAction({"Gift a flower", 'G'});

    CMenu::ActionList actions;
    actions.push_back(talkAction);

    if (_sympathy > 750)
    {
        actions.push_back(askOutAction);
    }

    if (CGameManagement::getInventoryInstance()->hasItem(CFlower::flowerFilter()))
    {
        actions.push_back(giftFlowerAction);
    }
    menu.addMenuGroup({actions});

    auto input = menu.execute();
    printHeader(false);

    if (input == talkAction)
    {
        talk();
        Console::confirmToContinue();
    }

    if (input == thinkAboutAction)
    {
        thinkAbout();
        Console::confirmToContinue();
    }

    if (input == giftFlowerAction)
    {
        giftFlower();
        Console::confirmToContinue();
    }

    return input;
}

std::string CNpc::translatorObjectName() const
{
    return std::string(TagNames::Translator::npc);
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
