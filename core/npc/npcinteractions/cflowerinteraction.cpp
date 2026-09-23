#include "cflowerinteraction.h"

#include "cflower.h"
#include "cgamemanagement.h"
#include "cnpc.h"
#include "console.h"
#include "randomizer.h"

CFlowerInteraction::CFlowerInteraction(CNpc* npc) : CNpcInteraction(npc, TagNames::NpcInteractions::flower)
{
    _favoriteFlower = Ressources::Items::getRandomFlowerType();
    _leastFavoriteFlower = Ressources::Items::getRandomFlowerType();
}

void CFlowerInteraction::executeInteraction()
{
    CNpcInteraction::executeInteraction();
    auto flower = CGameManagement::getInventoryInstance()->getFirstItemByFilter<CFlower>(CFlower::flowerFilter());
    if (!flower.has_value())
    {
        Console::printLn(
            coreTr("Well, this is emberrassing. You search your bag for flowers, but apperently you have none."));
        Console::printLn(coreTr("{} looks dissapointed.", _npc->name()));
        return;
    }

    Console::printLn(
        coreTr("You draw a {} out of your bag and hand it over to {}", flower.value()->name(), _npc->name()));
    switch (_npc->sympathy())
    {
    case CNpc::ESympathyLevel::eHate:
        Console::printLn(coreTr("You and {}, this did not go together well up to now. {} accepts the flower anyway.",
                                _npc->name(),
                                _npc->heShe()));
        break;
    case CNpc::ESympathyLevel::eDislike:
        Console::printLn(coreTr("You and {}, are not frieds at all. {} accepts the flower anyway as a peace offer.",
                                _npc->name(),
                                _npc->heShe()));
        break;
    case CNpc::ESympathyLevel::eNeutral:
    default:
        Console::printLn(
            coreTr("{} is surprised about your gift and {} takes it with a smile.", _npc->name(), _npc->heShe()));
        break;
    case CNpc::ESympathyLevel::eLike:
        Console::printLn(coreTr(
            "Your geasture hit the spot for {}. With a smile, {} accepts your gift.", _npc->name(), _npc->heShe()));
        break;
    case CNpc::ESympathyLevel::eLove:
        Console::printLn(coreTr(
            "A gift of love for {0}, {1} smiles as {1} taks your precious flower.", _npc->name(), _npc->heShe()));
        break;
    }

    if (flower.value()->flowerType() == _favoriteFlower && flower.value()->flowerType() != _leastFavoriteFlower)
    {
        Console::printLn(coreTr("{}s are {}s favourite flowers. {} loves your gift.",
                                Ressources::Items::flower2String(flower.value()->flowerType()),
                                _npc->name(),
                                _npc->heShe()));
        _npc->addSympathy(20 + Randomizer::getRandom(30));
    }
    else if (flower.value()->flowerType() == _leastFavoriteFlower && flower.value()->flowerType() != _favoriteFlower)
    {
        Console::printLn(coreTr("{} hates {}s. {} accepts your gesture.",
                                _npc->name(),
                                Ressources::Items::flower2String(flower.value()->flowerType()),
                                _npc->heShe()));
        _npc->addSympathy(5 + Randomizer::getRandom(10));
    }
    else
    {
        Console::printLn(coreTr("{} like {}s. {} takes the flowers with a smile.",
                                Ressources::Items::flower2String(flower.value()->flowerType()),
                                _npc->name(),
                                _npc->heShe()));
        _npc->addSympathy(5 + Randomizer::getRandom(10));
    }

    CGameManagement::getInventoryInstance()->removeItem(flower.value());
}

bool CFlowerInteraction::interactionAvailable() const
{
    return CNpcInteraction::interactionAvailable() &&
           CGameManagement::getInventoryInstance()->hasItem(CFlower::flowerFilter());
}

nlohmann::json CFlowerInteraction::save() const
{
    auto o = CNpcInteraction::save();
    o[TagNames::NpcInteractions::favouriteFlower] = _favoriteFlower;
    o[TagNames::NpcInteractions::leastFavouriteFlower] = _leastFavoriteFlower;
    return o;
}

void CFlowerInteraction::load(const nlohmann::json& json)
{

    CNpcInteraction::load(json);
    _favoriteFlower = json[TagNames::NpcInteractions::favouriteFlower];
    _leastFavoriteFlower = json[TagNames::NpcInteractions::leastFavouriteFlower];
}

void CFlowerInteraction::makeNav(CMenu& menu)
{
    _nav = menu.createAction({"Gift flower", 'G'});
}
