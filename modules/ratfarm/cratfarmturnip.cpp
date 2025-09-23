#include "cratfarmturnip.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "console.h"
#include "moduleressources.h"

#include <format>

CRatFarmTurnip::CRatFarmTurnip(const TurnipSize& size) : CItem(TagNames::RatFarm::turnip)
{
    std::string name;

    _description = std::format(
        "A {0} from the famous {1} farm in {1} ville, harvested by lady {1}. Probably the best {0} in the world.",
        RatFarmRessources::getTurnip(),
        RatFarmRessources::getCarrot());

    switch (size)
    {
    case TurnipSize::S:
        _name = std::format("half-eaten {}", RatFarmRessources::getTurnip());
        _description.append(" This one is half-eaten by a rat. delicious!");
        _value = 5;
        break;
    case TurnipSize::M:
    default:
        _name = RatFarmRessources::getTurnip();
        _value = 15;
        break;
    case TurnipSize::L:
        _name = std::format("Big {}", RatFarmRessources::getTurnip());
        _description.append(" This one is big and beautiful!");
        _value = 25;
        break;
    }

    _size = size;
    _isConsumable = true;
    _isUsableFromInventory = true;
    _isUsableFromBattle = true;
    _isSellable = true;
}

void CRatFarmTurnip::useFromInventory()
{
    Console::printLn("You are a little hungry, so let's eat");
    use();
}

void CRatFarmTurnip::useFromBattle(CEnemy*)
{
    Console::printLn("You should not have time for lunch in the middle of a fight, but maybe this helps.");
    use();
}

nlohmann::json CRatFarmTurnip::save() const
{
    auto o = CItem::save();
    o[TagNames::RatFarm::size] = _size;
    return o;
}

void CRatFarmTurnip::load(const nlohmann::json& json)
{
    _size = json.value<TurnipSize>(TagNames::RatFarm::size, TurnipSize::S);
}

void CRatFarmTurnip::use()
{
    unsigned int hp;
    switch (_size)
    {
    case TurnipSize::S:
        Console::printLn("Was good for the rat, is good for you!");
        hp = 1;
        break;
    case TurnipSize::M:
    default:
        hp = 2;
        break;
    case TurnipSize::L:
        Console::printLn("Actually, this is pretty tasty!");
        hp = 3;
        break;
    }
    CGameManagement::getPlayerInstance()->addHp(hp);
}
