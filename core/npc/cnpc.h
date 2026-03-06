#pragma once

#include "cgamestateobject.h"
#include "cmenu.h"
#include "cmenuaction.h"
#include "core.h"
#include "ressources.h"

#include <nlohmann/json.hpp>

class CMenu;
class CNpcInteraction;
class CEnemy;
/**
 * @brief class CNpc
 * represents an NPC
 * @remark abstract class, needs to be implemented
 */

class CNpc : public CGameStateObject
{
public:
    enum class ESympathyLevel
    {
        eHate = 0,
        eDislike = 1,
        eNeutral = 2,
        eLike = 3,
        eLove = 4,
    };

    /**
     * @brief Constructor
     */
    CNpc(const std::string_view& objectName, const Core::EGender gender);
    ~CNpc();

    /**
     * @brief Interaction functions
     * @remark must be re-implemented, but called if not abstract because most of them alter the relation to the player
     */

    /**
     * @brief interact
     * interact with the npc
     * @remark alters the relation to the player
     */
    virtual void interact();

    /**
     * @brief breakUp
     * removes NPC as significant other
     * @remark performs necessary checks before
     */
    virtual void breakUp();

    /**
     * @brief thinkAbout
     * prints the relationship status
     */
    void thinkAbout();

    /**
     * @brief name and description
     * must be implemented
     */
    virtual std::string name() const = 0;
    virtual std::string describe() const = 0;

    /**
     * @brief npcNac
     * provides a nav to interact with the NPC
     */
    virtual const CMenuAction npcNav(CMenu& menu) const;

    /**
     * @brief addSympathy
     * adds/removes sympathy
     */
    bool addSympathy(const int i);

    /**
     * @brief estrange
     * reduce sympathy through time
     */
    void estrange(const int i);

    /**
     * @brief estrange
     * increase sympathy through time
     */

    void reconcile(const int i);

    /**
     * @brief gender related stuff
     */
    std::string heShe() const;
    std::string hisHer() const;
    std::string himHer() const;
    std::string girlfriendBoyfriend() const;
    std::string notSeenString() const;

    /**
     * @brief getter
     */
    bool isSignificantOther() const;
    ESympathyLevel sympathy() const;
    bool isDatable() const;

    void setLastSeen(const int i);
    void setLastSeen();
    int turnsNotSeen() const;

    nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

    bool operator==(CNpc* other)
    {
        return getObjectName() == other->getObjectName();
    }

    virtual CEnemy* enemy() const;

protected:
    CMenuAction executeNpcMenu(CMenu& menu);

    virtual std::string translatorObjectName() const override;
    int _sympathy = 500;

    virtual void printHeader(const bool bFull = true) const = 0;
    void addInteraction(CNpcInteraction* interaction);

private:
    Core::EGender _gender;
    unsigned int _lastSeen = 0;
    std::vector<CNpcInteraction*> _interactions;
};