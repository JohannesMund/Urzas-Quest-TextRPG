#pragma once

#include "cgamestateobject.h"
#include "cmenu.h"
#include "cmenuaction.h"

#include <nlohmann/json.hpp>

class CMenu;
class CNpc : public CGameStateObject
{
public:
    CNpc(const std::string_view& objectName, const bool isFemale);

    virtual void interact() = 0;
    virtual void talk() = 0;
    virtual void thinkAbout() = 0;

    virtual std::string name() const = 0;
    virtual std::string describe() const = 0;

    virtual CMenuAction npcNav(CMenu& menu);
    bool addSympathy(const int i);

    nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

    bool operator==(CNpc* other)
    {
        return getObjectName() == other->getObjectName();
    }

    std::string heShe() const;
    std::string hisHer() const;

protected:
    CMenuAction executeNpcMenu(CMenu& menu);

    virtual std::string translatorObjectName() const override;
    int _sympathy = 500;

private:
    bool _female;
};