#pragma once

#include "cgamestateobject.h"
#include "cmenu.h"
#include "cmenuaction.h"

#include <nlohmann/json.hpp>

class CMenu;
class CNpc : public CGameStateObject
{
public:
    enum class ESympathyLevel
    {
        ehate = 0,
        eDislike = 1,
        eNeutral = 2,
        eLike = 3,
        eLove = 4,
    };

    CNpc(const std::string_view& objectName, const bool isFemale);

    virtual void interact();
    virtual void askOut();
    virtual void breakUp();
    virtual void talk() = 0;
    void thinkAbout();

    virtual std::string name() const = 0;
    virtual std::string describe() const = 0;

    virtual CMenuAction npcNav(CMenu& menu) const;
    bool addSympathy(const int i);

    nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

    bool operator==(CNpc* other)
    {
        return getObjectName() == other->getObjectName();
    }

    std::string heShe() const;
    std::string hisHer() const;
    bool isSignificantOther() const;
    ESympathyLevel sympathy() const;
    bool isDatable() const;

protected:
    CMenuAction executeNpcMenu(CMenu& menu);

    virtual std::string translatorObjectName() const override;
    int _sympathy = 500;

    virtual void printHeader(const bool bFull = true) const = 0;

private:
    void estrange(const int i);

    bool _female;
    unsigned int _lastSeen = 0;
};