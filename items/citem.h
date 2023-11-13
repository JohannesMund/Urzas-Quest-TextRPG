#pragma once

#include <functional>
#include <string>

class CEnemy;

/**
 * @brief The CItem class
 * Represents one Item. Virtual, Must be derived for full power
 */
class CItem
{
public:
    /**
     * @brief CItem
     * Constructor
     */
    CItem();

    virtual ~CItem()
    {
    }

    /**
     * Default items have no power. Needs to be overwritten to un-junk the item
     */

    /**
     * @brief useFromInventory
     * Called, when a n item is used from the enventory
     */
    virtual void useFromInventory()
    {
    }

    /**
     * @brief useFromBattle
     * Called, when an item is actively used from the inventory
     */
    virtual void useFromBattle(CEnemy*)
    {
    }

    /**
     * @brief battleEffect
     * @param enemy the current opponent
     * Called at the start of a battle
     */
    virtual void battleEffect(CEnemy* enemy)
    {
    }

    /**
     * @brief battleBuff
     * called every turn of the battle before the combattants select their action
     * @param enemy the current opponent
     * @param endRound ends the turn before the combattants can select an action
     */
    virtual void battleBuff(CEnemy* enemy, bool& endTurn)
    {
    }

    /**
     * @brief shield
     * Called, then the player recieved damage
     * @param i the damage that the player is about to take
     * @return the damage that is left after the shielding action
     */
    virtual int shield(const unsigned int i)
    {
        return i;
    }

    /**
     * @brief deathEffect
     * called whenever the player dies
     */
    virtual void deathEffect()
    {
    }

    /**
     * @brief view
     * Displays information abour the item
     */
    virtual void view();

    /**
     * @brief name
     * @return name of the item
     */
    virtual std::string name() const;
    /**
     * @brief description
     * @return desctiption of the item
     */
    std::string description() const;

    /**
     * @brief isSellable
     * @return is the item sellable
     */
    bool isSellable() const;

    /**
     * @brief value
     * @return the value of the item
     */
    virtual unsigned int value() const;

    /**
     * @brief value
     * @return the value, when a player wants to buy the item
     */
    virtual unsigned int buyValue() const;

    /**
     * @brief isUsableFromInventory
     * @return can the item be used from the inventory?
     */
    bool isUsableFromInventory() const;
    /**
     * @brief isUsableFromBattle
     * @return can the item be used during Battle?
     */
    bool isUsableFromBattle() const;

    /**
     * @brief hasDeathEffect
     * @return has the item an effect when the player dies?
     */
    bool hasDeathEffect() const;

    /**
     * @brief hasBattleEffect
     * @return has the item a passive effect at the start of the battle?
     */
    bool hasBattleEffect() const;

    /**
     * @brief hasDurableBattleEffect
     * @return has the item a passive effect during each battle round
     */
    bool hasDurableBattleEffect() const;

    /**
     * @brief hasShieldingAction
     * @return can the item shield damage
     */
    bool hasShieldingAction() const;

    /**
     * @brief isConsumable
     * @return is the item consumable
     * @remark this is checked everytime the item is used. so when the item has charges or so, set consumable to true,
     * when the charges are used up.
     */
    bool isConsumable() const;

    /**
     * @brief nameFilter
     * @param name
     * @return a name filter function to be used in std containers
     */
    static std::function<bool(const CItem*)> nameFilter(const std::string_view& name);

    /**
     * @brief battleEffectFilter
     * @return a filter function to filter items with battle effect from std containers
     */
    static std::function<bool(const CItem*)> battleEffectFilter();

    /**
     * @brief durableBattleEffectFilter
     * @return a filter function to filter items with durable battle effect from std containers
     */
    static std::function<bool(const CItem*)> durableBattleEffectFilter();

    /**
     * @brief shieldingActionFilter
     * @return a filter function to filter items with shield action from std containers
     */
    static std::function<bool(const CItem*)> shieldingActionFilter();

    /**
     * @brief deathEffectFilter
     @return a filter function to filter items with death effect from std containers
     */
    static std::function<bool(const CItem*)> deathEffectFilter();

protected:
    std::string _name;
    std::string _description;

    bool _isUsableFromInventory = false;
    bool _isUsableFromBattle = false;

    bool _hasDeathEffect = false;
    bool _hasBattleEffect = false;
    bool _hasBattleBuff = false;
    bool _hasShieldingAction = false;

    bool _isSellable = false;
    bool _isBuyable = false;
    unsigned int _value = 0;

    bool _isConsumable = false;
};
