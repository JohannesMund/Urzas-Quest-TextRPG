#pragma once

#include <cjunkitem.h>

class CBoatPart : public CJunkItem
{
public:
    enum class EPart
    {
        eBoard,
        eNail,
        eRope
    };

    CBoatPart();
    EPart part() const;

    static CItem::ItemFilter partFilter(const EPart part);
    static std::string nameForPart(const EPart part);

protected:
    virtual std::string translatorModuleName() const override;

    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

private:
    EPart _part;
};
