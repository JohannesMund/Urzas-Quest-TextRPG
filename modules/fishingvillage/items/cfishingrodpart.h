#pragma once

#include "cjunkitem.h"

class CFishingRodPart : public CJunkItem
{
public:
    enum class EPart
    {
        eRod,
        eThread,
        eHook
    };

    CFishingRodPart();

    EPart part() const;

    static CItem::ItemFilter partFilter(const EPart part);
    static std::string nameForPart(const EPart part);

protected:
    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

private:
    EPart _part;
};
